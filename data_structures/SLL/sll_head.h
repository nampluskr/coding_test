#pragma once

#include <cstdio>

struct DATA {
    int value, idx;

    DATA(int value = 0, int idx = -1) { this->value = value; this->idx = idx; }
    bool operator==(const DATA& data) const {
        return value == data.value && idx == data.idx;
    }
    bool operator<(const DATA& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
    void print() {
        printf("{ %d, %d }", value, idx);
    }
};

template<typename DATA>
struct SLL {
    struct NODE {
        DATA data;
        NODE* next;
    };
    NODE* head;
    int listSize = 0;

    // 생성자 정의
    SLL() { head = nullptr; listSize = 0; }

    // 기본 연산 멤버 함수 정의
    void push_front(const DATA& data);
    void pop_front();

    void push_back(const DATA& data);
    void pop_back();

    void clear();
    DATA front();
    DATA back();
    DATA& operator[](int idx);

    bool empty();
    int size();

    // 추가 연산 멤버 함수 정의
    NODE* find_ptr(const DATA& data);

    NODE* find_before(const DATA& data);
    void insert_after(NODE* ptr, const DATA& data);
    void erase_after(NODE* ptr);

    void remove(const DATA& data);
    int count(const DATA& data);

    // 보조 함수 정의
    void print();
    void preorder(NODE* ptr);
    void postorder(NODE* ptr);
    void show(NODE* ptr);

    struct ITER {
        NODE* ptr;

        ITER(NODE* ptr = nullptr) { this->ptr = ptr; }
        bool operator!=(const ITER& iter) const { return ptr != iter.ptr; }
        bool operator==(const ITER& iter) const { return ptr == iter.ptr; }
        DATA& operator*() { return ptr->data; }                 // *iter
        ITER& operator++() { ptr = ptr->next; return *this; }   // ++iter
        ITER operator++(int) { ITER iter = *this; ++(*this);  return iter; }
    };

    ITER begin() { return ITER(head); }
    ITER end() { return ITER(nullptr); }
    ITER find(const DATA& data) {
        for (auto iter = begin(); iter != end(); ++iter)
            if (*iter == data)
                return iter;
        return end();
    }
};