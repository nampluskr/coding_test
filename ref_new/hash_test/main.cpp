#include <cstdio>
#include <cstring>
#include "hash_test.h"

#define MAX_USERS   10
#define MAX_TABLE   10
#define MAX_KEYS    10

struct User {
    const char* ID;
    int value;
    const char* group;
};
User users[MAX_USERS];
int userCnt;
HashMap<const char*> userMap;
UnorderedMap<const char*, LinkedList<int>, MAX_KEYS> userList;

int get_userIndex(const char* ID) {
    int uIdx;
    auto ret = userMap.find(ID);
    if (ret == -1) {
        uIdx = userCnt++;
        userMap.emplace(ID, uIdx);
    }
    else { uIdx = ret; }
    return uIdx;
}

////////////////////////////////////////////////////////////////////
void init() {
    for (int i = 0; i < MAX_USERS; i++) { users[i] = {}; }
    userCnt = 0;
    userMap.clear();
    userList.clear();
}

void add(const char* ID, int value, const char* group) {
    int uIdx = get_userIndex(ID);
    users[uIdx] = { ID, value, group };
    userList[group].push_back(uIdx);
}

int main()
{
    init();

    //add(111, 10, 1);
    //add(222, 20, 1);
    //add(333, 30, 2);
    //add(444, 40, 1);
    //add(111, 50, 2);

    add("aaa", 10, "A");
    add("bbb", 20, "A");
    add("ccc", 30, "B");
    add("ddd", 40, "A");
    add("aaa", 50, "B");
    
    printf("%d\n", 1 << 10);

    return 0;
}