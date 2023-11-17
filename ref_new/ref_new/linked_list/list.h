#pragma once

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;     // = nullptr;
    ListNode* tail;     // = nullptr;
    int listSize;

    void clear() { head = nullptr; tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        listSize += 1;
    }
    void push_front(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { node->next = head; head = node; }
        listSize += 1;
    }
    void pop_front() {
        ListNode* temp = head;
        head = temp->next;
        if (head == nullptr) { tail = nullptr; }
        delete temp;
        listSize -= 1;
    }
    Type front() { return head->data; }
    Type back() { return tail->data; }
    bool empty() { return listSize == 0; }
    int size() { return listSize; }
};


template<typename Type>
struct Stack {
    LinkedList<Type> lst;

    void clear() { lst.clear(); }
    void push(const Type& data) { lst.push_front(data); }
    void pop() { lst.pop_front(); }
    Type top() { return lst.front(); }
    bool empty() { return lst.empty(); }
    int size() { return lst.size(); }
};


template<typename Type>
struct Queue {
    LinkedList<Type> lst;

    void clear() { lst.clear(); }
    void push(const Type& data) { lst.push_back(data); }
    void pop() { lst.pop_front(); }
    Type front() { return lst.front(); }
    bool empty() { return lst.empty(); }
    int size() { return lst.size(); }
};


void print_list(const LinkedList<int>& lst);
