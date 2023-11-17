## [STL] Hash Chaining for Strings

```cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

#define NUM_USERS   101
#define MAX_TABLE   7007

struct User {
    int x;
    int y;
};
User users[NUM_USERS];
int userCnt;

unordered_map<string, vector<int>> userList;
unordered_map<string, int> userMap;

int get_userIndex(const char key[]) {
    int uIdx;
    auto ret = userMap.find(key);
    if (ret == userMap.end()) {
        uIdx = userCnt;
        userMap.emplace(key, uIdx);
        userCnt += 1;
    }
    else { uIdx = ret->second; }
    return uIdx;
}

int main()
{
    // Hash Chaining
    userList.clear();

    //userList.emplace("aaa", 10);
    userList["aaa"].push_back(10);
    userList["aaa"].push_back(20);
    userList["aaa"].push_back(30);

    for (auto uIdx: userList["aaa"]) {
        printf("%d\n", uIdx);
    }

    // Hash Mapping
    userMap.clear();

    printf("(%s, %d)\n", "aaa", get_userIndex("aaa"));
    printf("(%s, %d)\n", "bbb", get_userIndex("bbb"));
    printf("(%s, %d)\n", "ccc", get_userIndex("ccc"));
    printf("(%s, %d)\n", "ddd", userMap["ddd"]);

    return 0;
}
```

## [Manual] Hash Chaining for Strings

```cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdio.h>

#define NUM_USERS   101
#define MAX_TABLE   7007

struct User {
    int x;
    int y;
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

// unordered_map<string, vector<Type>> userList;
template<typename Type>
struct HashChain {
    LinkedList<Type> table[MAX_TABLE];

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
    //void emplace(const char key[], Type value) {
    //    int hashkey = hash(key);
    //    table[hashkey].push_back(value);
    //}
    LinkedList<Type>& operator[](const char key[]) {
        int hashkey = hash(key);
        return table[hashkey];
    }
};
HashChain<int> userList;

// unordered_map<string, int> userMap;
struct HashMap {
    struct Data {
        char key[11];
        int value;
        Data() { strcpy(this->key, ""); this->value = 0; }
        Data(const char key[], int value) { strcpy(this->key, key); this->value = value; }
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
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
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
    int operator[](const char key[]) {
        return find(key);
    }
};
HashMap userMap;

int get_userIndex(const char key[]) {
    int uIdx;
    auto ret = userMap.find(key);
    if (ret == -1) {
        uIdx = userCnt;
        userMap.emplace(key, uIdx);
        userCnt += 1;
    }
    else { uIdx = ret; }
    return uIdx;
}

int main()
{
    // Hash Chaining
    userList.clear();

    //userList.emplace("aaa", 10);
    userList["aaa"].push_back(10);
    userList["aaa"].push_back(20);
    userList["aaa"].push_back(30);

    for (auto node = userList["aaa"].head; node; node=node->next) {
        printf("%d\n", node->data);
    }

    // Hash Mapping
    userMap.clear();

    printf("(%s, %d)\n", "aaa", get_userIndex("aaa"));
    printf("(%s, %d)\n", "bbb", get_userIndex("bbb"));
    printf("(%s, %d)\n", "ccc", get_userIndex("ccc"));
    printf("(%s, %d)\n", "ddd", userMap["ddd"]);

    return 0;
}
```
