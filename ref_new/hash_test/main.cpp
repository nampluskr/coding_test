#include <cstring>
#include "hash_test.h"

#define MAX_TABLE   10

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;     // = nullptr;
    ListNode* tail;     // = nullptr;
    int listSize;       // = 0;

    void clear() { head = nullptr; tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        listSize += 1;
    }
};


template<typename Type>
int hashfunc(Type key) {
    return key % MAX_TABLE;
}

template<> int hashfunc(const char* key) { 
    unsigned long long hash = 5381;
    int c;
    while (c = *key++) { hash = (((hash << 5) + hash) + c) % MAX_TABLE; }
    return hash;
}

template<typename Type>
int compare(Type a, Type b) { return (a == b) ? 0: -1; }

template<> int compare(const char* a, const char* b) {
    return strcmp(a, b);
}

template<typename Type>
struct HashMap {
    struct KeyValue {
        Type key;
        int value;
    };
    LinkedList<KeyValue> table[MAX_TABLE];

    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    int find(Type key) {
        int hash = hashfunc(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (compare(ptr->data.key, key) == 0)
                return ptr->data.value;
        }
        return -1;
    }
    void emplace(Type key, int value) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, value });
    }
};

HashMap<const char*> strMap;
int strCnt = 0;

HashMap<unsigned long long> intMap;
int intCnt = 0;

int get_strIndex(const char* key) {
    int idx;
    auto ret = strMap.find(key);
    if (ret == -1) {
        idx = strCnt++;
        strMap.emplace(key, idx);
    }
    else { idx = ret; }
    return idx;
}

int get_intIndex(unsigned long long key) {
    int idx;
    auto ret = intMap.find(key);
    if (ret == -1) {
        idx = intCnt++;
        intMap.emplace(key, idx);
    }
    else { idx = ret; }
    return idx;
}

#define MAX_KEYS    10

template<typename Type1, typename Type2>
struct UnorderedMap {
    Type2 objects[MAX_KEYS];
    int objectCnt;
    HashMap<Type1> objectMap;

    void clear() {
        for (int i = 0; i < MAX_KEYS; i++) { objects[i] = {}; }
        objectCnt = 0;
        objectMap.clear();
    }
    int getIndex(Type1 key) {
        int idx;
        auto ret = objectMap.find(key);
        if (ret == -1) {
            idx = objectCnt++;
            objectMap.emplace(key, idx);
        }
        else { idx = ret; }
        return idx;
    }
    Type2& operator[](Type1 key) {
        int idx = getIndex(key);
        return objects[idx];
    }
};

UnorderedMap<const char*, LinkedList<int>> strListMap;
UnorderedMap<unsigned long long, LinkedList<int>> intListMap;

int main()
{
    int idx;

    strMap.clear();
    idx = get_strIndex("aaa");
    idx = get_strIndex("bbb");
    idx = get_strIndex("ccc");

    intMap.clear();
    idx = get_intIndex(111);
    idx = get_intIndex(222);
    idx = get_intIndex(333);

    strListMap.clear();
    strListMap["aaa"].push_back(100);
    strListMap["aaa"].push_back(200);
    strListMap["aaa"].push_back(300);

    intListMap.clear();
    intListMap[1111].push_back(100);
    intListMap[1111].push_back(200);
    intListMap[1111].push_back(300);

    return 0;
}