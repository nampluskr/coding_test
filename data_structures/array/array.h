#pragma once

template<typename T, int max_size>
struct Array {
    T array[max_size];
    int head = tail = -1;
    int arraySize = 0;

    void clear() { head = tail = -1; arraySize = 0; }
    bool empty() { return arraySize == 0; }
    int size() { return listSize; }

    // Access
    T& operator[](int idx) { return array[idx]; }
    T front() { return array[head]; }
    T back() { return array[back]; }

    // Insert
    void push_front(const T& data);
    void push_back(const T& data);

    // Remove
    void pop_front();
    void pop_back();
};

// Insert
template<typename T, int max_size>
void Array<T, max_size>::push_front(const T& data) {}

template<typename T, int max_size>
void Array<T, max_size>::push_back(const T& data) {}

// Remove
template<typename T, int max_size>
void Array<T, max_size>::pop_front() {}

template<typename T, int max_size>
void Array<T, max_size>::pop_back() {}