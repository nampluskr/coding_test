#pragma once
#include <cstdio>

template<typename T>
struct ListNode {
    T data;
    ListNode* next;
};

template<typename T>
struct Queue {
    ListNode<T>* head = nullptr;
    ListNode<T>* tail = nullptr;
    int nodeCnt = 0;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {  // push_back
        ListNode<T>* node = new ListNode<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        nodeCnt++;
    }
    void pop() {                // pop_front
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
        nodeCnt--;
        if (head == nullptr) { tail = nullptr; }
    }
    T front() { return head->data; }
    bool empty() { return nodeCnt == 0; }
};

template<typename T>
struct Stack {
    ListNode<T>* head = nullptr;
    ListNode<T>* tail = nullptr;
    int nodeCnt = 0;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {  // push_front
        ListNode<T>* node = new ListNode<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        nodeCnt++;
    }
    void pop() {                // pop_front
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
        nodeCnt--;
        if (head == nullptr) { tail = nullptr; }
    }
    T top() { return head->data; }
    bool empty() { return nodeCnt == 0; }
};

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