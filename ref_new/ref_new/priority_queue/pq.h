#pragma once

#include <queue>
using namespace std;

template<typename Type>
struct PQ{
    priority_queue<Type> heap;

    void clear() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};


#define MAX_HEAP    1000
template<typename Type>
struct PriorityQueue {
    Type heap[MAX_HEAP];
    int heapSize;

    void clear() { heapSize = 0; }
    void push(const Type& data) {
        heap[heapSize] = data;
        int cur = heapSize;
        while (cur > 0 && heap[(cur - 1) / 2] < heap[cur]) {
            Type temp = heap[(cur - 1) / 2];
            heap[(cur - 1) / 2] = heap[cur];
            heap[cur] = temp;
            cur = (cur - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int cur = 0;
        while (cur * 2 + 1 < heapSize) {
            int child;
            if (cur * 2 + 2 == heapSize) { child = cur * 2 + 1; }
            else {
                child = heap[cur * 2 + 2] < heap[cur * 2 + 1] ? cur * 2 + 1 : cur * 2 + 2;
            }
            if (heap[child] < heap[cur]) { break; }
            Type temp = heap[cur];
            heap[cur] = heap[child];
            heap[child] = temp;
            cur = child;
        }
    }
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
    int size() { return heapSize; }
};
