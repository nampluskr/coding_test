#pragma once

#include <queue>
using namespace std;


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

#define MAX_TABLE   107

int intHash(unsigned long long key) {
    return key % MAX_TABLE;
}

struct IntMapInt {
    struct Pair {
        unsigned long long key; int value;
    };
    LinkedList<Pair> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int find(unsigned long long key) {
        int hash = intHash(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (ptr->data.key == key) { return ptr->data.value; }
        }
        return -1;
    }
    void emplace(unsigned long long key, int value) {
        int hash = intHash(key);
        table[hash].push_back({ key, value });
    }
};


template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void clear() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

