## [STL] Hash Chaining for Strings

```cpp
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

#define NUM_USERS   100
#define MAXL        11

struct User {
    string userID;
    int point;
};

unordered_map<string, int> userMap;
vector<User> users;
int userCnt;

int get_userIndex(string userID) {
    int uIdx;
    auto ret = userMap.find(userID);
    if (ret == userMap.end()) {
        uIdx = userCnt;
        userMap.emplace(userID, uIdx);
        userCnt += 1;
    }
    else { uIdx = ret->second; }
    return uIdx;
}

void init() {
    userMap.clear();
    users.clear();  users.resize(NUM_USERS);
    userCnt = 0;
}

void add(string userID, int point) {
    int uIdx = get_userIndex(userID);
    users[uIdx] = { userID, point };
}

int main()
{
    init();
    add("aaaaa", 10);
    add("bbbbb", 20);
    add("ccccc", 30);

    printf("(%s, %d)\n", "aaaaa", get_userIndex("aaaaa"));
    printf("(%s, %d)\n", "bbbbb", get_userIndex("bbbbb"));
    printf("(%s, %d)\n", "ccccc", get_userIndex("ccccc"));

    return 0;
}
```

## [Manual] Hash Chaining for Strings

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define NUM_USERS   100
#define MAXL        11
#define MAX_TABLE   7007

struct User {
    char userID[MAXL];
    int point;

    User() { strcpy(userID, ""); point = 0; }
    User(const char _userID[], int _point) { strcpy(userID, _userID); point = _point; }
};

User users[NUM_USERS];
int userCnt;

struct UnorderedMap_Str {
    struct ListNode {
        char key[MAXL];
        int value;
        ListNode* next;
    };
    ListNode heap[NUM_USERS];
    int heapSize;
    ListNode* table[MAX_TABLE];

    void clear() { heapSize = 0; }
    int hash(const char key[]) {
        unsigned long hash = 5381;
        int c;

        while (c = *key++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    int find(const char key[]) {
        int hashkey = hash(key);
        for (auto node = table[hashkey]; node; node = node->next)
            if (strcmp(node->key, key) == 0)
                return node->value;
        return -1;
    }
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        strcpy(heap[heapSize].key, key);
        heap[heapSize].value = value;
        heap[heapSize].next = table[hashkey];

        table[hashkey] = &heap[heapSize];
        heapSize += 1;
    }
};
UnorderedMap_Str userMap;

int get_userIndex(const char userID[]) {
    int uIdx;
    auto ret = userMap.find(userID);
    if (ret == -1) {
        uIdx = userCnt;
        userMap.emplace(userID, uIdx);
        userCnt += 1;
    }
    else { uIdx = ret; }
    return uIdx;
}

void add(const char userID[], int point) {
    int uIdx = get_userIndex(userID);
    users[uIdx] = { userID, point };
}

void init() {
    userMap.clear();
    for (int i = 0; i < NUM_USERS; i++) { users[i] = { "", 0 }; }
    userCnt = 0;
}

int main()
{
    init();
    add("aaaaa", 10);
    add("bbbbb", 20);
    add("ccccc", 30);

    printf("(%s, %d)\n", "aaaaa", get_userIndex("aaaaa"));
    printf("(%s, %d)\n", "bbbbb", get_userIndex("bbbbb"));
    printf("(%s, %d)\n", "ccccc", get_userIndex("ccccc"));

    return 0;
}
```