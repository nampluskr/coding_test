#if 0
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
struct BST {
    struct NODE {
        DATA data;
        NODE* left;
        NODE* right;
    };
    NODE* root;
    int treeSize;

    // ������ ����
    BST() { root = nullptr; treeSize = 0; }

    // �⺻ ��� �Լ�
    NODE* new_node(const DATA& data);
    NODE* insert_node(NODE* ptr, const DATA& data);
    void insert(const DATA& data);
    NODE* find(NODE* ptr, const DATA& data);    // recursive
    NODE* find(const DATA& data);               // iterative
    void clear();

    NODE* remove(NODE* ptr, const DATA& data);  // recursive
    void remove(const DATA& data);              // iterative

    // �߰� ��� �Լ�
    NODE* find_min(NODE* ptr, NODE** min_node);
    DATA top();
    DATA bottom();

    // ���� ��� �Լ�
    NODE* inorder(NODE* ptr);
    void print();

};
#endif