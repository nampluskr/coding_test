#pragma once

#define MAX_HEAP    1000

#include <queue>
using namespace std;

template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void clear() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};


template<typename Type>
struct DoubleEndedPQ {
    struct MaxData {
        Type data; int cnt;
        bool operator<(const MaxData& x) const { return data < x.data; }
    };
    struct MinData {
        Type data; int cnt;
        bool operator<(const MinData& x) const { return !(data < x.data); }
    };
    PriorityQueue<MaxData> maxHeap;
    PriorityQueue<MinData> minHeap;
    bool popped[MAX_HEAP];      // #define MAX_HEAP 1000
    int cnt, heapSize;

    void clear() {
        while (!maxHeap.empty()) { maxHeap.pop(); }
        while (!minHeap.empty()) { minHeap.pop(); }
        for (int i = 0; i < MAX_HEAP; i++) { popped[i] = false; }
        cnt = 0;
        heapSize = 0;
    }
    void push(const Type& data) {
        maxHeap.push({ data, cnt });
        minHeap.push({ data, cnt });
        popped[cnt++] = false;
        heapSize += 1;
    }
    void pop_top() {
        while (!maxHeap.empty() && popped[maxHeap.top().cnt]) { maxHeap.pop(); }
        popped[maxHeap.top().cnt] = true; maxHeap.pop();
        heapSize -= 1;
    }
    void pop_bottom() {
        while (!minHeap.empty() && popped[minHeap.top().cnt]) { minHeap.pop(); }
        popped[minHeap.top().cnt] = true; minHeap.pop();
        heapSize -= 1;
    }
    Type top() {
        while (!maxHeap.empty() && popped[maxHeap.top().cnt]) { maxHeap.pop(); }
        return maxHeap.top().data;
    }
    Type bottom() {
        while (!minHeap.empty() && popped[minHeap.top().cnt]) { minHeap.pop(); }
        return minHeap.top().data;
    }
    bool empty() { return heapSize == 0; }
    int size() { return heapSize; }
};