#pragma once

struct DATA {
    int value, idx;

    bool operator==(const DATA& data) const {
        return (value == data.value) && (idx == data.idx);
    }
};

template<typename DATA>
struct SLL {
    struct NODE {
        DATA data;
        NODE* next;
    };
    NODE* head;
    NODE* tail;
    int listSize;

    void init() { head = nullptr; listSize = 0; }
    void clear() { while(!empty()) pop_front(); }
    NODE* new_node(const DATA& data, NODE* ptr = nullptr);
    void delete_node(NODE* ptr);
    void preorder(NODE* ptr);

    // 기본 연산
    void push_front(const DATA& data);
    void push_back(const DATA& data);
    void pop_front();
    void pop_back();

    NODE* find(const DATA& data);
    void remove(const DATA& data);

    // 보조 함수
    NODE* find_before(const DATA& data);
    void insert_after(NODE* ptr, const DATA& data);
    void erase_after(NODE* ptr);

    // 데이터 접근
    DATA front() { return head->data; }
    DATA back() { return tail->data; }
    DATA& operator[](int idx);

    // 리스트 정보
    bool empty() { return listSize == 0; }
    int size() { return listSize; }
};