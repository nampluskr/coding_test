#pragma once

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


template<typename Key>
int hashfunc(Key key, int max_table) {
    return key % max_table;
}

template<> int hashfunc(const char* key, int max_table) {
    unsigned long long hash = 5381;
    int c;
    while (c = *key++) { hash = (((hash << 5) + hash) + c) % max_table; }
    return hash;
}


template<typename Key, int max_table = 5007>
struct HashMap {
    struct Pair {
        Key key;
        int value;
    };
    LinkedList<Pair> table[max_table];

    void clear() {
        for (int i = 0; i < max_table; i++)
            table[i].clear();
    }
    int find(Key key) {
        int hash = hashfunc(key, max_table);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (ptr->data.key == key)
                return ptr->data.value;
        }
        return -1;
    }
    void emplace(Key key, int value) {
        int hash = hashfunc(key, max_table);
        table[hash].push_back({ key, value });
    }
};


template<typename Key, typename Object, int max_keys, int max_table = 5007>
struct UnorderedMap {
    HashMap<Key, max_table> groupMap;
    Object groups[max_keys];
    int groupCnt;

    void clear() {
        for (int i = 0; i < max_keys; i++) { groups[i] = {}; }
        groupCnt = 0;
        groupMap.clear();
    }
    int getIndex(Key key) {
        int idx;
        auto ret = groupMap.find(key);
        if (ret == -1) {
            idx = groupCnt++;
            groupMap.emplace(key, idx);
        }
        else { idx = ret; }
        return idx;
    }
    Object& operator[](Key key) {
        int idx = getIndex(key);
        return groups[idx];
    }
};