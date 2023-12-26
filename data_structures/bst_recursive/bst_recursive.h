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
struct BST {
    struct NODE {
        DATA data;
        NODE* left;
        NODE* right;
    };
    NODE* root;
    int treeSize;

    void init() { root = nullptr; treeSize = 0; }
    NODE* new_node(const DATA& data, NODE* ptr1 = nullptr, NODE* ptr2 = nullptr) {
        printf(">> Insert % d[%d]\n", data.value, data.idx);
        NODE* node = new NODE{ data, ptr1, ptr2 };
        treeSize += 1;
        return node;
    }
    void delete_node(NODE* ptr) {
        printf(">> Remove % d[%d]\n", ptr->data.value, ptr->data.idx);
        delete ptr;
        treeSize -= 1;
    }
    void inorder(NODE* ptr);

    // 기본 연산 recursive / iterative
    NODE* clear(NODE* ptr);
    NODE* insert(NODE* ptr, const DATA& data);
    NODE* remove(NODE* ptr, const DATA& data);
    NODE* find(NODE* ptr, const DATA& data);
    NODE* find_min(NODE* ptr);
    NODE* find_max(NODE* ptr);

    // 트리 정보
    bool empty() { return root == nullptr; }
    int size() { return treeSize; }
    DATA top() { return find_min(root)->data; }
    DATA bottom() { return find_max(root)->data; }
};