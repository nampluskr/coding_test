#pragma once

template<typename T, int max_size>
struct Stack {
    T list[max_size];
    int listSize = 0;
    int head, tail;

    void clear() { head = tail = -1; listSize = 0; }
    void push(const T& data) {
        if (listSize == max_size) return;
        tail++;
        if (head == -1) { head++; }
        list[tail] = data;
        listSize++;
    }
    void pop() {
        if (listSize == 0) return;
        tail--;
        if (tail < head) { head = tail = -1; }
        listSize--;
    }
    bool empty() { return listSize == 0; }
    T top() { return list[tail]; }
    int size() { return listSize; }
};

template<typename T, int max_size>
struct Queue {
    T list[max_size];
    int listSize = 0;
    int head, tail;

    void clear() { head = tail = -1; listSize = 0; }
    void push(const T& data) {
        if (listSize == max_size) return;
        tail++;
        if (head == -1) { head++; }
        list[tail] = data;
        listSize++;
    }
    void pop() {
        if (listSize == 0) return;
        head++;
        if (head > tail) { head = tail = -1; }
        listSize--;
    }
    bool empty() { return listSize == 0; }
    T front() { return list[head]; }
    int size() { return listSize; }
};