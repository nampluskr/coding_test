#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <cstring>
using namespace std;

#define MAX_ROOMS	(30000 + 1)
#define MAX_WORD    (11 + 1)

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

# define MAX_TABLE 30001
struct HashMap {
    struct MapData {
        char key[MAX_WORD];
        int value;

        MapData() { strcpy_s(this->key, ""); this->value = 0; }
        MapData(const char key[], int value) { strcpy_s(this->key, key); this->value = value; }
    };
    LinkedList<MapData> table[MAX_TABLE];

    int hash(const char* str) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int find(const char key[]) {
        int hashkey = hash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (strcmp(node->data.key, key) == 0)
                return node->data.value;
        }
        return -1;
    }
    int operator[](const char key[]) {
        return find(key);
    }
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
};

struct Room {
    int mID;
    char mWord[MAX_WORD];
    char dir[3][MAX_WORD];
};
Room rooms[MAX_ROOMS];
HashMap roomMap;
int current_roomID;

struct Data {
    int mID;
    char mWord[MAX_WORD];

    Data() { this->mID = 0; strcpy_s(this->mWord, ""); }    // 없으면 C2280 에러
    Data(int mID, const char mWord[]) { this->mID = mID; strcpy_s(this->mWord, mWord); }
    bool operator<(const Data& data) const { return strcmp(mWord, data.mWord) > 0; }
};

template<typename Type>
struct PriorityQueue {
    vector<Type> heap;
    //Type heap[10000];     // 메모리 초과
    int heapSize;

    void clear() { 
        heap.clear(); 
        heapSize = 0; }
    void push(const Type& data) {
        if (heapSize >= heap.size()) { heap.push_back({}); }

        heap[heapSize] = data;
        int current = heapSize;
        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            Type temp = heap[(current - 1) / 2];
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
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current]) {
                break;
            }
            Type temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    bool empty() { return heapSize == 0; }
    Type top() { return heap[0]; }
};

HashMap dirMap[3];
PriorityQueue<Data> dirPQ[3][MAX_ROOMS];
int dirMapCnt[3];

int get_mapIndex(int mDir, const char subWord[]) {
    int mIdx;
    auto ret = dirMap[mDir].find(subWord);
    if (ret == -1) {
        mIdx = dirMapCnt[mDir]++;
        dirMap[mDir].emplace(subWord, mIdx);
    }
    else { mIdx = ret; }
    return mIdx;
}

//////////////////////////////////////////////////////////////////////////////
void init()
{
    for (int i = 0; i < MAX_ROOMS; i++) { rooms[i] = {}; }
    roomMap.clear();

    for (int i = 0; i < 3; i++) {
        dirMap[i].clear();
        dirMapCnt[i] = 0;
        for (int j = 0; j < MAX_ROOMS; j++)
            dirPQ[i][j].clear();
    }
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    rooms[mID].mID = mID;
    strcpy_s(rooms[mID].mWord, mWord);
    strncpy_s(rooms[mID].dir[0], mWord, mDirLen[0]);
    strncpy_s(rooms[mID].dir[1], mWord + 4, mDirLen[1]);
    strncpy_s(rooms[mID].dir[2], mWord + 11 - mDirLen[2], mDirLen[2]);

    roomMap.emplace(mWord, mID);

    int mIdx;
    char subWord[5];
    strncpy_s(subWord, mWord + 9, 2);  mIdx = get_mapIndex(0, subWord); dirPQ[0][mIdx].push({ mID, mWord });
    strncpy_s(subWord, mWord + 7, 4);  mIdx = get_mapIndex(0, subWord); dirPQ[0][mIdx].push({ mID, mWord });
    strncpy_s(subWord, mWord + 4, 3);  mIdx = get_mapIndex(1, subWord); dirPQ[1][mIdx].push({ mID, mWord });
    strncpy_s(subWord, mWord + 0, 2);  mIdx = get_mapIndex(2, subWord); dirPQ[2][mIdx].push({ mID, mWord });
    strncpy_s(subWord, mWord + 0, 4);  mIdx = get_mapIndex(2, subWord); dirPQ[2][mIdx].push({ mID, mWord });
}

void setCurrent(char mWord[])
{
    current_roomID = roomMap[mWord];
}

int moveDir(int mDir)
{
    char subWord[MAX_WORD];
    strcpy_s(subWord, rooms[current_roomID].dir[mDir]);

    int mIdx = get_mapIndex(mDir, subWord);
    auto& Q = dirPQ[mDir][mIdx];

    int ret = 0;
    LinkedList<int> popped;
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (strcmp(rooms[data.mID].mWord, data.mWord) != 0) continue;

        popped.push_back(data.mID);
        if (data.mID != current_roomID) {
            ret = data.mID;
            break;
        }
    }
    for (auto node = popped.head; node; node = node->next) {
        int mID = node->data;
        Q.push({ mID, rooms[mID].mWord }); }
    if (ret != 0) { current_roomID = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[mWord];
    addRoom(mID, mChgWord, mChgLen);
}
#endif
