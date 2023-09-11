#if 0
// (TC = 5) Manual-1 50 ms / STL-1 88 ms / Brute force 646 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

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

template<typename Type>
struct HashChain {
    LinkedList<Type> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    LinkedList<Type>& operator[](int key) {
        int hashkey = key % MAX_TABLE;
        return table[hashkey];
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

HashChain<int> logoutAccList;

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
    logoutAccList.clear();
}

void NewAccount(char id[], char password[], int defaulttime)
{
    int aIdx = get_accountIndex(id);
    strcpy(accounts[aIdx].password, password);
    accounts[aIdx].default_time = defaulttime;
    accounts[aIdx].logout_time = current_time + defaulttime;

    logoutAccList[accounts[aIdx].logout_time].push_back(aIdx);
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

    accounts[aIdx].logout_time = current_time + accounts[aIdx].default_time;
    logoutAccList[accounts[aIdx].logout_time].push_back(aIdx);
}

int Tick()
{
    current_time += 1;

    int ret = 0;
    for (auto node = logoutAccList[current_time].head; node; node = node->next) {
        int aIdx = node->data;
        if (accounts[aIdx].logout_time != current_time) continue;

        if (accounts[aIdx].state != LOGOUT) {
            accounts[aIdx].state = LOGOUT;
            ret += 1;
        }
    }
    return ret;
}
#endif