#pragma once

template<typename T>
inline void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T, int max_size>
struct PQ {
    T heap[max_size];
    int heapSize = 0;

    void clear() { heapSize = 0; }
    void push(const T& data);
    void pop();
    bool empty() { return heapSize == 0; }
    T top() { return heap[1]; }
    int size() { return heapSize; }
};

template<typename T, int max_size>
void PQ<T, max_size>::push(const T& data) {
    if (heapSize == max_size - 1) return;   // 예외 처리

    // 마지막 다음 자리에 데이터 추가
    heapSize += 1;
    heap[heapSize] = data;

    // 상위 노드로 이동하면서 부모 노드값과 비교 및 교체
    int cur = heapSize;
    int parent = cur / 2;
    while (parent >= 1) {
        if (heap[cur] < heap[parent]) break;
        swap(heap[cur], heap[parent]);
        cur = parent;
        parent = cur / 2;
    }
}

template<typename T, int max_size>
void PQ<T, max_size>::pop() {
    if (heapSize == 0) return;      // 예외 처리

    // 맨 앞 노드에 마지막 배열값 대입
    heap[1] = heap[heapSize];
    heapSize -= 1;

    // 하위 노드로 이동하면서 자식 노드값(왼쪽, 오른쪽)과 비교 및 교체
    int cur = 1;
    int child = cur * 2;
    while (child + 1 <= heapSize) {
        if (heap[child] < heap[child + 1]) child += 1;
        if (heap[child] < heap[cur]) break;
        swap(heap[child], heap[cur]);
        cur = child;
        child = cur * 2;
    }
}