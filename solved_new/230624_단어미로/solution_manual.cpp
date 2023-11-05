#if 1
// STL 584 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_ROOMS   (30000 + 1)
#define MAX_LEN     (11 + 1)

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

template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void clear() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};

#define MAX_TABLE   5007

int hashfunc(const char key[]) {
    unsigned long hash = 5381;
    int c;
    while (c = *key++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

struct HashMapInt {
    struct KeyValue {
        char key[MAX_LEN];
        int value;

        KeyValue(const char key[], int value) {
            strcpy(this->key, key);
            this->value = value;
        }
    };
    LinkedList<KeyValue> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int find(const char key[]) {
        int hash = hashfunc(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (strcmp(ptr->data.key, key) == 0) { return ptr->data.value; }
        }
        return -1;
    }
    void emplace(const char key[], int value) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, value });
    }
    int operator[](const char key[]) {
        return find(key);
    }
};

template<typename Type>
struct HashMapPQ {
    HashMapInt hashmap;
    PriorityQueue<Type> table[MAX_TABLE];

    void clear() { 
        hashmap.clear();
        for (int i = 0; i < MAX_TABLE; i++) table[i].clear();
    }
    PriorityQueue<Type>& operator[](const char key[]) {
        int hash = hashfunc(key);
        return table[hash];
    }
};

struct Room {
    char mWord[MAX_LEN];
    char mDirWord[3][4 + 1];
};
//vector<Room> rooms;
Room rooms[MAX_ROOMS];
int roomCnt;
HashMapInt roomMap;

int currentRoomID;

struct Data {
    char mWord[MAX_LEN];
    char dirWord[4 + 1];
    int mID;

    Data(const char mWord[], const char dirWord[], int mID) {
        strcpy(this->mWord, mWord);
        strcpy(this->dirWord, dirWord);
        this->mID = mID;
    }
    bool operator<(const Data& data) const { return strcmp(mWord, data.mWord) > 0; }
};
unordered_map<string, PriorityQueue<Data>> moveDirMap[3];
//HashMapPQ<Data> moveDirMap[3];

////////////////////////////////////////////////////////////////////
void init()
{
    //rooms.clear();  rooms.resize(MAX_ROOMS);
    for (int i = 0; i < MAX_ROOMS; i++) { rooms[i] = {}; }
    roomCnt = 0;
    roomMap.clear();

    for (int i = 0; i < 3; i++) { moveDirMap[i].clear(); }
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    roomCnt++;
    roomMap.emplace(mWord, mID);

    strcpy(rooms[mID].mWord, mWord);
    strncpy_s(rooms[mID].mDirWord[0], mWord + 0, mDirLen[0]);
    strncpy_s(rooms[mID].mDirWord[1], mWord + 4, mDirLen[1]);
    strncpy_s(rooms[mID].mDirWord[2], mWord + 11 - mDirLen[2], mDirLen[2]);

    char dirWord[4 + 1];
    strncpy_s(dirWord, mWord + 9, 2); moveDirMap[0][dirWord].push({ mWord, dirWord, mID });
    strncpy_s(dirWord, mWord + 7, 4); moveDirMap[0][dirWord].push({ mWord, dirWord, mID });
    strncpy_s(dirWord, mWord + 4, 3); moveDirMap[1][dirWord].push({ mWord, dirWord, mID });
    strncpy_s(dirWord, mWord + 0, 2); moveDirMap[2][dirWord].push({ mWord, dirWord, mID });
    strncpy_s(dirWord, mWord + 0, 4); moveDirMap[2][dirWord].push({ mWord, dirWord, mID });
}

void setCurrent(char mWord[])
{
    int mID = roomMap[mWord];
    currentRoomID = mID;
}

int moveDir(int mDir)
{
    auto& Q = moveDirMap[mDir][rooms[currentRoomID].mDirWord[mDir]];
    LinkedList<int> popped; popped.clear();
    int ret = 0;

    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (strcmp(rooms[data.mID].mWord, data.mWord) != 0) continue;
        //if (strcmp(rooms[data.mID].mDirWord[2 - mDir], data.dirWord) != 0) continue;

        popped.push_back(data.mID);
        if (data.mID != currentRoomID) {
            ret = data.mID;
            break;
        }
    }
    for (auto ptr = popped.head; ptr; ptr = ptr->next) {
        int mID = ptr->data;
        Q.push({ rooms[mID].mWord, rooms[mID].mDirWord[mDir], mID});
    }
    if (ret != 0) { currentRoomID = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[mWord];
    addRoom(mID, mChgWord, mChgLen);
}
#endif