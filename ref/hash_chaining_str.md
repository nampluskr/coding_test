## [STL] Hash Chaining for Strings

```cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

#define NUM_USERS   100
#define MAXL        11

struct User {
    char userID[MAXL];
    int point;
    User() { strcpy(userID, ""); point = 0; }
    User(const char _userID[], int _point) { strcpy(userID, _userID); point = _point; }
};

unordered_map<string, int> userMap;
vector<User> users;
int userCnt;

int get_userIndex(const char userID[]) {
    int uIdx;
    auto ret = userMap.find(string(userID));
    if (ret == userMap.end()) {
        uIdx = userCnt;
        userMap.emplace(string(userID), uIdx);
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

void add(const char userID[], int point) {
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
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

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

struct UnorderedMap_Str {
    struct Data {
        char key[MAXL];
        int value;
        Data(const char _key[], int _value) { strcpy(key, _key); value = _value; }
    };
    LinkedList<Data> table[MAX_TABLE];

    unsigned long hash(const char str[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) { table[i].clear(); }
    }
    int find(const char key[]) {
        int hashkey = hash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            auto data = node->data;
            if (strcmp(data.key, key) == 0)
                return data.value;
        }
        return -1;
    }
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
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
    for (int i = 0; i < NUM_USERS; i++) { users[i] = {}; }
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