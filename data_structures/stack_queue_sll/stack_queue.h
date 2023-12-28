#pragma once

template<typename T>
struct NODE {
    T data;
    NODE* next;
};

template<typename T>
struct Stack {
    NODE<T>* head = nullptr;
    NODE<T>* tail = nullptr;
    int listSize = 0;

    void clear() { while(!empty()) pop(); }
    void push(const T& data) {  // push_front()
        NODE<T>* node = new NODE<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        listSize++;
    }
    void pop() {                // pop_front()
        NODE<T>* temp = head;
        head = head->next;
        if (head == nullptr) { tail = nullptr; }
        delete temp;
        listSize--;
    }
    bool empty() { return listSize == 0; }
    T top() { return head->data; }
    int size() { return listSize; }
};


template<typename T>
struct Queue{
    NODE<T>* head = nullptr;
    NODE<T>* tail = nullptr;
    int listSize = 0;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {  // push_back()
        NODE<T>* node = new NODE<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        listSize++;
    }
    void pop() {                // pop_front()
        NODE<T>* temp = head;
        head = head->next;
        if (head == nullptr) { tail = nullptr; }
        delete temp;
        listSize--;
    }
    bool empty() { return listSize == 0; }
    T front() { return head->data; }
    int size() { return listSize; }
};
