#pragma once

struct DATA {
    int value, idx;

    bool operator==(const DATA& data) const {
        return (value == data.value) && (idx == data.idx);
    }
    bool operator<(const DATA& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

template<typename DATA>
struct LIST {
    struct NODE {
        DATA data;
        NODE* next;
    };
    NODE* head;
    int listSize;

    void init() { head = nullptr; listSize = 0; }
    NODE* new_node(const DATA& data, NODE* ptr = nullptr) {
        printf(">> Insert % d[%d]\n", data.value, data.idx);
        NODE* node = new NODE{ data, ptr };
        listSize += 1;
        return node;
    }
    void delete_node(NODE* ptr) {
        printf(">> Remove % d[%d]\n", ptr->data.value, ptr->data.idx);
        delete ptr;
        listSize -= 1;
    }

    // 기본 연산 (반복문 이용)
    void clear();
    void insert(const DATA& data);
    void remove(const DATA& data);
    NODE* find(const DATA& data);
    NODE* find_min();
    void preorder();

    // 리스트 정보
    bool empty() { return head == nullptr; }
    int size() { return listSize; }
    DATA top() { return head->data; }
    DATA bottom() { return find_min(head)->data; }
};