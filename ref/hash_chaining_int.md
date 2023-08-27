## [STL] Hash Chaining for Integers

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

#define NUM_USERS   100

struct User {
    int userID;
    int point;
};

unordered_map<int, int> userMap;
vector<User> users;
int userCnt;

int get_userIndex(int userID) {
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

void add(int userID, int point) {
    int uIdx = get_userIndex(userID);
    users[uIdx] = { userID, point };
}

int main()
{
    init();
    add(1000, 10);
    add(2000, 20);
    add(3000, 30);

    printf("(%d, %d)\n", 1000, get_userIndex(1000));
    printf("(%d, %d)\n", 2000, get_userIndex(2000));
    printf("(%d, %d)\n", 3000, get_userIndex(3000));

    return 0;
}
```

## [Manual] Hash Chaining for Integers

```cpp
#include <stdio.h>

#define NUM_USERS   100
#define MAX_TABLE   7007

struct User {
    int userID;
    int point;
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

struct UnorderedMap_Int {
    struct Data {
        int key;
        int value;
    };
    LinkedList<Data> table[MAX_TABLE];

    int hash(int key) { return key % MAX_TABLE; }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) { table[i].clear(); }
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
    void emplace(int key, int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
};
UnorderedMap_Int userMap;

int get_userIndex(int userID) {
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

void add(int userID, int point) {
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
    add(1000, 10);
    add(2000, 20);
    add(3000, 30);

    printf("(%d, %d)\n", 1000, get_userIndex(1000));
    printf("(%d, %d)\n", 2000, get_userIndex(2000));
    printf("(%d, %d)\n", 3000, get_userIndex(3000));

    return 0;
}
```