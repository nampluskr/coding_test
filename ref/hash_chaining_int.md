## [STL] Hash Chaining for Integers

```cpp
#include <stdio.h>
#include <vector>
#include <unordered_map>
using namespace std;

#define NUM_USERS   101
#define MAX_TABLE   7007

struct User {
    int x;
    int y;
};
User users[NUM_USERS];
int userCnt;

unordered_map<int, vector<int>> userList;
unordered_map<int, int> userMap;

int get_userIndex(int key) {
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

    //userList.emplace(11111, 10);
    userList[11111].push_back(10);
    userList[11111].push_back(20);
    userList[11111].push_back(30);

    for (auto uIdx: userList[11111]) {
        printf("%d\n", uIdx);
    }

    // Hash Mapping
    userMap.clear();

    printf("(%d, %d)\n", 11111, get_userIndex(11111));
    printf("(%d, %d)\n", 22222, get_userIndex(22222));
    printf("(%d, %d)\n", 33333, get_userIndex(33333));
    printf("(%d, %d)\n", 44444, userMap[44444]);

    return 0;
}
```

## [Manual] Hash Chaining for Integers

```cpp
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

// unordered_map<int, vector<Type>> userList
template<typename Type>
struct HashChain {
    LinkedList<Type> table[MAX_TABLE];

    int hash(int key) {
        return key % MAX_TABLE;
    }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) { table[i].clear(); }
    }
    //void emplace(int key, Type value) {
    //    int hashkey = hash(key);
    //    table[hashkey].push_back(value);
    //}
    LinkedList<Type>& operator[](int key) {
        int hashkey = hash(key);
        return table[hashkey];
    }
};
HashChain<int> userList;

// unordered_map<int, int> userMap;
struct HashMap {
    struct Data {
        int key;
        int value;
    };
    LinkedList<Data> table[MAX_TABLE];

    int hash(int key) {
        return key % MAX_TABLE;
    }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) { table[i].clear(); }
    }
    void emplace(int key, int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
    int find(int key) {
        int hashkey = hash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            auto data = node->data;
            if (data.key == key)
                return data.value;
        }
        return -1;
    }
    int operator[](int key) {
        return find(key);
    }
};
HashMap userMap;

int get_userIndex(int key) {
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

    //userList.emplace(11111, 10);
    userList[11111].push_back(10);
    userList[11111].push_back(20);
    userList[11111].push_back(30);

    for (auto node = userList[11111].head; node; node = node->next) {
        printf("%d\n", node->data);
    }

    // Hash Mapping
    userMap.clear();

    printf("(%d, %d)\n", 11111, get_userIndex(11111));
    printf("(%d, %d)\n", 22222, get_userIndex(22222));
    printf("(%d, %d)\n", 33333, get_userIndex(33333));
    printf("(%d, %d)\n", 44444, userMap[44444]);

    return 0;
}
```
