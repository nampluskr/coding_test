#pragma once
#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
};

template<typename T>
struct BinaryTree {
    Node<T>* root = nullptr;
    int treeSize = 0;

    Node<T>* new_node(const T& data, Node<T>* left, Node<T>* right) {
        Node<T>* node = new Node<T>{ data, left, right };
        treeSize++;
        return node;
    }
    void delete_node(Node<T>* ptr) {
        delete ptr;
        treeSize--;
    }
    bool empty() { return treeSize == 0; }
    int size() { return treeSize; }
};

template<typename T>
void preorder(Node<T>* ptr) {
    if (ptr == nullptr) return;     // base case
    printf("[%d]->", ptr->data);    // visit the node
    preorder(ptr->left);
    preorder(ptr->right);
}

template<typename T>
void inorder(Node<T>* ptr) {
    if (ptr == nullptr) return;     // base case
    inorder(ptr->left);
    printf("[%d]->", ptr->data);    // visit the node
    inorder(ptr->right);
}

template<typename T>
void postorder(Node<T>* ptr) {
    if (ptr == nullptr) return;     // base case
    postorder(ptr->left);
    postorder(ptr->right);
    printf("[%d]->", ptr->data);    // visit the node
}

template<typename T>
void preorder_iterative(Node<T>* ptr) {
    stack<Node<T>*> S;
    S.push(ptr);

    while (!S.empty()) {
        ptr = S.top(); S.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->right != nullptr) { S.push(ptr->right); }
        if (ptr->left != nullptr) { S.push(ptr->left); }
    }
}

template<typename T>
void level_order(Node<T>* ptr) {
    queue<Node<T>*> Q;
    Q.push(ptr);

    while (!Q.empty()) {
        ptr = Q.front(); Q.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->left != nullptr)
            Q.push(ptr->left);
        if (ptr->right != nullptr)
            Q.push(ptr->right);
    }
}

template<typename T>
int count_nodes(Node<T>* ptr) {
    if (ptr == nullptr) { return 0; }
    return 1 + count_nodes(ptr->left) + count_nodes(ptr->right);
}

template<typename T>
int sum_nodes(Node<T>* ptr) {
    if (ptr == nullptr) { return 0; }
    return ptr->data + sum_nodes(ptr->left) + sum_nodes(ptr->right);
}

inline int max(int a, int b) { return (a < b) ? b : a; }

template<typename T>
int height_tree(Node<T>* ptr) {
    if (ptr == nullptr) { return 0; }
    return 1 + max(height_tree(ptr->left), height_tree(ptr->right));
}

template<typename T>
int leaf_nodes(Node<T>* ptr) {
    if (ptr == nullptr) { return -1; }
    if (ptr->left == 0 && ptr->right == 0) { return 10; }
    
    return leaf_nodes(ptr->left) + leaf_nodes(ptr->right);
}
