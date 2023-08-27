#if 0
// Bruet force 2168 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>

#define NUM_USERS   500000
#define LOGIN   0
#define LOGOUT  1

struct User {
    char id[11];
    char password[11];
    int default_time;

    int login_time;
    int state;
};
User users[NUM_USERS];
int userCnt;

//////////////////////////////////////////////////////////////////////////////
#define MAX_TABLE   50007

unsigned long hashfunc(const char key[]) {
    unsigned long hash = 5381;
    int c;
    while (c = *key++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    void init() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data){
        ListNode* node = new ListNode({data, nullptr});
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

LinkedList<int> head[MAX_TABLE];

int get_userIndex(const char id[]) {
    int hashkey = hashfunc(id);
    for (auto ptr = head[hashkey].head; ptr; ptr = ptr->next) {
        int i = ptr->data;
        if (strcmp(users[i].id, id) == 0)
            return i;
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////
void Init()
{
    for (int i = 0; i < NUM_USERS; i++) { users[i] = {}; }
    userCnt = 0;

    for (int i = 0; i < MAX_TABLE; i++) { head[i].init(); }
}

void NewAccount(char id[11], char password[11], int defaulttime) {
    int uIdx = userCnt;
    strcpy(users[uIdx].id, id);
    strcpy(users[uIdx].password, password);
    users[uIdx].default_time = defaulttime;
    users[uIdx].login_time = defaulttime;
    users[uIdx].state = LOGIN;

    int hashkey = hashfunc(id);
    head[hashkey].push_back(uIdx);
    userCnt += 1;
}

void Logout(char id[11]) {
    int uIdx = get_userIndex(id);
    if (users[uIdx].state == LOGIN) {
        users[uIdx].state = LOGOUT;
    }
}

void Connect(char id[11], char password[11])
{
    int uIdx = get_userIndex(id);
    //if (strcmp(users[uIdx].id, id) != 0) return;
    if (strcmp(users[uIdx].password, password) != 0) return;
    if (users[uIdx].state == LOGIN) {
        users[uIdx].login_time = users[uIdx].default_time;
    }
}

int Tick()
{
    int ret = 0;
    for (int i = 0; i < userCnt; i++) {
        if (users[i].state != LOGOUT) {
            users[i].login_time -= 1;

            if (users[i].login_time == 0) {
                users[i].state = LOGOUT;
                ret += 1;
            }
        }
    }
    return ret;
}
#endif