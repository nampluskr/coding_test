#if 1
// Manual 769 ms: 
// vector clear(), resize() -> 배열 / 초기화
// vector -> Linked List
// 문자열 비교: strcpy(), strcmp()
// priority_queue -> manual pq

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define LEN_WORD    (11 + 1)
#define NUM_ROOMS   (30000 + 1)

struct Room {
    int mID;
    char word[LEN_WORD];
    string dir[3];      // 접두어, 가운데, 접미어

    Room() {
        mID = 0;
        strcpy(word, "");
        for (int i = 0; i < 3; i++) { dir[i].clear(); }
    }
};
unordered_map<string, int> roomMap;
Room rooms[NUM_ROOMS];
int current_mID;

struct Data {
    int mID;
    char word[LEN_WORD];

    Data() { mID = 0; strcpy(word, ""); }
    Data(int _mID, char _word[]) { mID = _mID; strcpy(word, _word); }
    bool operator<(const Data& room) const { return strcmp(word, room.word) > 0; }
};

#if 1
struct PriorityQueue {
    priority_queue<Data> heap;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Data& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Data top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
struct PriorityQueue {
    vector<Data> heap;
    int heapSize = 0;

    void init() { heap.clear(); heapSize = 0; }
    void push(const Data& data) {
        if (heapSize >= heap.size())
            heap.push_back({});

        heap[heapSize] = data;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current]) {
            Data temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int current = 0;

        while (current * 2 + 1 < heapSize) {
            int child;
            if (current * 2 + 2 == heapSize)
                child = current * 2 + 1;
            else
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;

            if (heap[child] < heap[current])
                break;

            Data temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    Data top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
};
#endif
unordered_map<string, PriorityQueue> dirMap[3];

struct LinkedList {
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;

    void init() { head = nullptr; tail = nullptr; }
    void push_back(int value) {
        Node* node = new Node({ value, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

//////////////////////////////////////////////////////////////
void init()
{
    for (int i = 0; i < NUM_ROOMS; i++) { rooms[i] = Room(); }
    roomMap.clear();

    for (int i = 0; i < 3; i++) { dirMap[i].clear(); }
}

// 30,000
// mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.
void addRoom(int mID, char mWord[], int mDirLen[])
{
    string word = string(mWord);
    rooms[mID].mID = mID;
    strcpy(rooms[mID].word, mWord);
    rooms[mID].dir[0] = word.substr(0, mDirLen[0]);                 // 앞 방향
    rooms[mID].dir[1] = word.substr(4, mDirLen[1]);                 // 중간 방향
    rooms[mID].dir[2] = word.substr(11 - mDirLen[2], mDirLen[2]);   // 뒤 방향

    roomMap[string(mWord)] = mID;

    dirMap[0][word.substr(9, 2)].push({ mID, mWord });   // 접미어 -> 앞 방향
    dirMap[0][word.substr(7, 4)].push({ mID, mWord });   // 접미어 -> 앞 방향
    dirMap[1][word.substr(4, 3)].push({ mID, mWord });   // 가운데 -> 중간 방향
    dirMap[2][word.substr(0, 2)].push({ mID, mWord });   // 접두어 -> 뒤 방향
    dirMap[2][word.substr(0, 4)].push({ mID, mWord });   // 접두어 -> 뒤 방향
}

// 500
void setCurrent(char mWord[])
{
    current_mID = roomMap[string(mWord)];
}

// 50,000
// 사전 순으로 가장 빠른 단어가 있는 방으로 이동
int moveDir(int mDir)
{
    string word = rooms[current_mID].dir[mDir];
    PriorityQueue& Q = dirMap[mDir][word];
    LinkedList popped; popped.init();
    int ret = 0;

    while (!Q.empty()) {
        Data room = Q.top(); Q.pop();

        if (strcmp(rooms[room.mID].word, room.word) != 0) continue;

        popped.push_back(room.mID);
        if (room.mID != current_mID) {
            ret = room.mID;
            break;
        }
    }
    for (auto node = popped.head; node; node = node->next) {
        int mID = node->value;
        Q.push({ mID, rooms[mID].word });
    }
    if (ret != 0) { current_mID = ret; }
    return ret;
}

// 30,000
void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[string(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}
#endif