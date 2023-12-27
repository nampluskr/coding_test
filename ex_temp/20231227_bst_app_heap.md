### Expression Tree 계산

```cpp
template<typename T>
int eval(NODE<T>* ptr) {
    if (ptr == nullptr) { return 0; }
    if (!ptr->left && !ptr->right) { return ptr->data; }

    int op = ptr->data;
    int val1 = eval(ptr->left);
    int val2 = eval(ptr->right);

    printf(">> %d %c %d\n", val1, op, val2);
    switch (op) {
    case '+': return val1 + val2;
    case '-': return val1 - val2;
    case '*': return val1 * val2;
    case '/': return val1 / val2;
    }
    return 0;
}
```

### 노드 합 / 개수 / 리프 개수 / 높이 계산

```cpp
int get_sum(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return ptr->data + get_sum(ptr->left) + get_sum(ptr->right);
}

int get_count(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return 1 + get_count(ptr->left) + get_count(ptr->right);
}

int get_leaf_count(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    if (!ptr->left && !ptr->right) return 1;
    return get_leaf_count(ptr->left) + get_leaf_count(ptr->right);
}

int max(int a, int b) { return (a < b) ? b : a; }

int get_height(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return 1 + max(get_height(ptr->left), get_height(ptr->right));
}
```

### Max. Heap 구현

```cpp
template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T, int max_size>
struct PriorityQueue {
    T heap[max_size];   // 첫 인덱스 1, 마지막 인덱스 max_size
    int heapSize = 0;   // 원소 개수 max_size - 1 까지 (0 제외)

    void clear() { heapSize = 0; }
    void push(const T& data);
    void pop();
    bool empty() { return heapSize == 0; }
    T top() { return heap[1]; }
    int size() { return heapSize; }
};

template<typename T, int max_size>
void PriorityQueue<T, max_size>::push(const T& data) {
    if (heapSize == max_size - 1) return;   // 예외 처리
    
    // 배열 마지막 다음 위치 에 원소 추가
    heapSize += 1;
    heap[heapSize] = data;

    // 상위 노드로 올라가면서 부모 노드값과 비교 / 교체
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
void PriorityQueue<T, max_size>::pop() {
    if (heapSize == 0) return;      // 예외 처리

    // 배열 첫 위치 마지막 원소 대입
    heap[1] = heap[heapSize];
    heapSize -= 1;

    // 하위 노드로 내려가면서 자식 노드값과 비교 / 교체
    int cur = 1;
    int child = cur * 2;              // 왼쪽 자식
    while (child + 1 <= heapSize) {   // 오른족 자식
        if (heap[child] < heap[child + 1]) child += 1;
        if (heap[child] < heap[cur]) break;
        swap(heap[cur], heap[child]);

        cur = child;
        child = cur * 2;
    }
}
```

### Heap test 코드

```cpp
#include <cstdio>
#include "heap.h"

struct DATA {
    int value, idx;
    bool operator<(const DATA& data) const {
        return (value < data.value) || 
            (value == data.value && idx > data.idx);
    }
};

PriorityQueue<DATA, 100> Q;

int main()
{
    Q.clear();
    Q.push({ 17, 0 });
    Q.push({ 29, 1 });
    Q.push({ 27, 2 });
    Q.push({ 15, 3 });
    Q.push({ 34, 4 });

    while (!Q.empty()) {
        auto top = Q.top(); Q.pop();
        printf(">> Popped: %d[%d]\n", top.value, top.idx);
    }


    return 0;
}
```
