#if 0
// STL 78 ms / Manual 48 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

#define MAX_LEN     (10 + 1)
#define MAX_USERS   (50000 + 1)
#define MAX_TIME    (50000 + 1)
#define LOGOUT      1

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

#define MAX_TABLE   50007
struct HashMap {
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
    int hashfunc(const char key[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *key++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    int find(const char key[]) {
        int hash = hashfunc(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (strcmp(ptr->data.key, key) == 0) {
                return ptr->data.value;
            }
        }
        return -1;
    }
    void emplace(const char key[], int value) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, value });
    }
};

struct User {
    char password[MAX_LEN];
    int defaultTime;
    int logoutTime;
    int state;
};
User users[MAX_USERS];
int userCnt;
HashMap userMap;

int currentTime;
LinkedList<int> logoutUserList[MAX_TIME];

////////////////////////////////////////////////////////////////////
int get_userIndex(const char id[]) {
    int uIdx;
    auto ptr = userMap.find(id);
    if (ptr == -1) {
        uIdx = userCnt++;
        userMap.emplace(id, uIdx);
    }
    else { uIdx = ptr; }
    return uIdx;
}

////////////////////////////////////////////////////////////////////
void Init() {
    for (int i = 0; i < MAX_USERS; i++) { users[i] = {}; }
    userCnt = 0;
    userMap.clear();

    currentTime = 0;
    for (int i = 0; i < MAX_TIME; i++) { logoutUserList[i].clear(); }
}

void NewAccount(char id[11], char password[11], int defaulttime) {
    int uIdx = get_userIndex(id);

    strcpy(users[uIdx].password, password);
    users[uIdx].defaultTime = defaulttime;
    users[uIdx].logoutTime = currentTime + defaulttime;

    logoutUserList[users[uIdx].logoutTime].push_back(uIdx);
}

void Logout(char id[11]) {
    int uIdx = get_userIndex(id);

    if (users[uIdx].state != LOGOUT) {
        users[uIdx].state = LOGOUT;
    }
}

void Connect(char id[11], char password[11]) {
    int uIdx = get_userIndex(id);

    if (strcmp(users[uIdx].password, password) != 0) { return; }
    if (users[uIdx].state != LOGOUT) {
        users[uIdx].logoutTime = currentTime + users[uIdx].defaultTime;
        logoutUserList[users[uIdx].logoutTime].push_back(uIdx);
    }
}

int Tick() {
    currentTime += 1;
    int ret = 0;

    for (auto ptr = logoutUserList[currentTime].head; ptr; ptr = ptr->next) {
        int uIdx = ptr->data;
        if (users[uIdx].state == LOGOUT) continue;

        if (users[uIdx].logoutTime == currentTime) {
            users[uIdx].state = LOGOUT;
            ret += 1;
        }
    }
    return ret;
}
#endif