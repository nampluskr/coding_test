#pragma once

#include <cstring>

#define MAX_TABLE           5007
#define KNUTH_MAX_TABLE     1024
#define MAX_KEYS            1000

int intHash(int key);
int knuthHash(int key);
int strHash(const char key[]);


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


struct StrMapInt {
    struct Pair {
        char key[11]; int value;
        Pair() { strcpy_s(this->key, ""); this->value = 0; }
        Pair(const char key[], int value) {
            strcpy_s(this->key, key); this->value = value;
        }
    };
    LinkedList<Pair> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int find(const char key[]) {
        int hash = strHash(key);
        for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
            if (strcmp(ptr->data.key, key) == 0) { return ptr->data.value; }
        }
        return -1;
    }
    void emplace(const char key[], int value) {
        int hash = strHash(key);
        table[hash].push_back({ key, value });
    }
};


template<typename Type>
struct IntMap {
    Type objects[MAX_KEYS];
    int objectCnt;
    IntMapInt objectMap;

    void clear() {
        for (int i = 0; i < MAX_KEYS; i++) { objects[i] = {}; }
        objectCnt = 0;
        objectMap.clear();
    }
    int getIndex(unsigned long long key) {
        int idx;
        auto ret = objectMap.find(key);
        if (ret == -1) {
            idx = objectCnt++;
            objectMap.emplace(key, idx);
        }
        else { idx = ret; }
        return idx;
    }
    Type& operator[](unsigned long long key) {
        int idx = getIndex(key);
        return objects[idx];
    }
};


template<typename Type>
struct StrMap {
    Type objects[MAX_KEYS];
    int objectCnt;
    StrMapInt objectMap;

    void clear() {
        for (int i = 0; i < MAX_KEYS; i++) { objects[i] = {}; }
        objectCnt = 0;
        objectMap.clear();
    }
    int getIndex(const char key[]) {
        int idx;
        auto ret = objectMap.find(key);
        if (ret == -1) {
            idx = objectCnt++;
            objectMap.emplace(key, idx);
        }
        else { idx = ret; }
        return idx;
    }
    Type& operator[](const char key[]) {
        int idx = getIndex(key);
        return objects[idx];
    }
};