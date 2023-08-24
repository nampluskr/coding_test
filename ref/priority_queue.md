## [STL] Priority Queue

```cpp
#include <queue>
using namespace std;

struct Data {
    int value1;
    int value2;

    bool operator<(const Data& data) const {
        return (value2 > data.value2) || (value2 == data.value2 && value1 < data.value1);
    }
};

priority_queue<Data> Q;
#else
template<typename Type>
struct PriorityQueue {
    priority_queue<Data> heap;

    void clear() { while (!heap.empty()) { heap.pop(); } }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

PriorityQueue<Data> Q;

int main()
{
    // 초기화
    //while (!Q.empty()) { Q.pop(); }
    Q.clear();

    // 입력
    Q.push({ 3, 30 });
    Q.push({ 2, 20 });
    Q.push({ 1, 10 });

    // 크기
    int size = Q.size();
    printf("%d\n", size);

    // 탐색
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```

## [Manual] Priority Queue

```cpp
#include <stdio.h>
#define MAX_SIZE 100000

struct Data {
    int value1;
    int value2;

    bool operator<(const Data& data) const {
        return (value2 > data.value2) || (value2 == data.value2 && value1 < data.value1);
    }
};

template<typename Type>
struct PriorityQueue {
    Type heap[MAX_SIZE];
    int heapSize = 0;

    void clear() { heapSize = 0; }
    void push(const Type& data) {
        heap[heapSize] = data;
        int current = heapSize;
        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            Type temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int current = 0;

        while (current * 2 + 1 < heapSize) {
            int child;
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current]) {
                break;
            }
            Type temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
    int size() { return heapSize; }
};

PriorityQueue<Data> Q;

int main()
{
    // 초기화
    //while (!Q.empty()) { Q.pop(); }
    Q.clear();

    // 입력
    Q.push({ 3, 30 });
    Q.push({ 2, 20 });
    Q.push({ 1, 10 });

    // 크기
    int size = Q.size();
    printf("%d\n", size);

    // 탐색
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```
