#if 1
// (TC = 5) Manual-2 47 ms / Manual-1 50 ms / STL-2 61 ms / STL-1 88 ms / Brute force 646 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
#include <queue>
using namespace std;

#define NUM_ACCOUNTS    50000
#define MAX_LENGTH      11
#define LOGOUT          1
#define MAX_TABLE       50007

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct HashMap {
    struct Data {
        char key[MAX_LENGTH];
        int value;

        //Data() { strcpy(this->key, ""); this->value = 0; }
        Data(const char key[], int value) { strcpy(this->key, key); this->value = value; }
    };
    LinkedList<Data> table[MAX_TABLE];

    int hash(const char str[]) {
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
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
};

//////////////////////////////////////////////////////////////////////////////

struct Account {
    char password[MAX_LENGTH];
    int default_time;
    int logout_time;
    int state;
};
Account accounts[NUM_ACCOUNTS];
int accountCnt;

HashMap accountMap;
int current_time;

struct Data {
    int aIdx;
    int logout_time;
    bool operator<(const Data& data) const { return logout_time > data.logout_time; }
};

#define MAX_SIZE 50000

template<typename Type>
struct PriorityQueue {
    Type heap[MAX_SIZE];
    int heapSize = 0;

    void clear() { heapSize = 0; }
    void push(const Type& data) {
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
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
};

PriorityQueue<Data> logoutAccPQ;

//////////////////////////////////////////////////////////////////////////////
int get_accountIndex(const char id[]) {
    int aIdx;
    auto ret = accountMap.find(id);
    if (ret == -1) {
        aIdx = accountCnt;
        accountMap.emplace(id, aIdx);
        accountCnt += 1;
    }
    else { aIdx = ret; }
    return aIdx;
}

//////////////////////////////////////////////////////////////////////////////
void Init()
{
    for (int i = 0; i < NUM_ACCOUNTS; i++) { accounts[i] = {}; }
    accountCnt = 0;
    accountMap.clear();
    current_time = 0;

    logoutAccPQ.clear();
    //while (!logoutAccPQ.empty()) { logoutAccPQ.pop(); }
}

void NewAccount(char id[], char password[], int defaulttime)
{
    int aIdx = get_accountIndex(id);
    strcpy(accounts[aIdx].password, password);
    accounts[aIdx].default_time = defaulttime;

    int logout_time = current_time + defaulttime;
    accounts[aIdx].logout_time = logout_time;
    logoutAccPQ.push({ aIdx, logout_time });
}

void Logout(char id[])
{
    int aIdx = get_accountIndex(id);
    accounts[aIdx].state = LOGOUT;
}

void Connect(char id[], char password[])
{
    int aIdx = get_accountIndex(id);
    if (strcmp(accounts[aIdx].password, password) != 0) return;
    if (accounts[aIdx].state == LOGOUT) return;

    int logout_time = current_time + accounts[aIdx].default_time;
    accounts[aIdx].logout_time = logout_time;
    logoutAccPQ.push({ aIdx, logout_time });
}

int Tick()
{
    current_time += 1;

    int ret = 0;
    auto& Q = logoutAccPQ;

    while (!Q.empty() && Q.top().logout_time <= current_time) {
        auto data = Q.top(); Q.pop();
        int aIdx = data.aIdx;

        if (accounts[aIdx].logout_time != current_time) continue;

        if (accounts[aIdx].state != LOGOUT) {
            accounts[aIdx].state = LOGOUT;
            ret += 1;
        }
    }
    return ret;
}
#endif