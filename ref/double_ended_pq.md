### [Double-ended Priority Queue]

```cpp
#if 1
#include <vector>
#include <queue>

using namespace std;

#define NUM_DATA 100

struct Data {
    int value1, value2;
    bool operator<(const Data& data) const {
        return (value1 < data.value1) ||
            (value1 == data.value1 && value2 > data.value2);
    }
};

template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void init() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};

template<typename Type>
struct DoubleEndedPQ {
    struct minData {
        Type data;
        int idx;
        bool operator<(const minData& x) const { return !(data < x.data); }
    };
    struct maxData {
        Type data;
        int idx;
        bool operator<(const maxData& x) const { return data < x.data; }
    };

    PriorityQueue<minData> minHeap;
    PriorityQueue<maxData> maxHeap;
    bool isPopped[NUM_DATA];
    int idx = 0;
    int size = 0;

    void init() {
        for (int i = 0; i < NUM_DATA; i++) { isPopped[i] = false; }
        minHeap.init();
        maxHeap.init();
        idx = 0;
        size = 0;
    }
    void push(const Data& data) {
        minHeap.push({ data, idx });
        maxHeap.push({ data, idx });
        idx += 1;
        size += 1;
    }
    void popMax() {
        while (!maxHeap.empty() && isPopped[maxHeap.top().idx])
            maxHeap.pop();
        isPopped[maxHeap.top().idx] = true;
        maxHeap.pop();
        size -= 1;
    }
    void popMin() {
        while (!minHeap.empty() && isPopped[minHeap.top().idx])
            minHeap.pop();
        isPopped[minHeap.top().idx] = true;
        minHeap.pop();
        size -= 1;
    }
    Type top() {
        while (!maxHeap.empty() && isPopped[maxHeap.top().idx])
            maxHeap.pop();
        return maxHeap.top().data;
    }
    Type bottom() {
        while (!minHeap.empty() && isPopped[minHeap.top().idx])
            minHeap.pop();
        return minHeap.top().data;
    }
    bool empty() { return size == 0; }
};

PriorityQueue<Data> P;
DoubleEndedPQ<Data> Q;

int main() {

    Q.init();

    Q.push({ 1, 1 });
    Q.push({ 1, 2 });
    Q.push({ 1, 3 });
    Q.push({ 2, 1 });
    Q.push({ 2, 2 });
    Q.push({ 2, 3 });

    auto top = Q.top();
    auto bottom = Q.bottom();

    while (!Q.empty()) {
    	Data max_data = Q.top(); Q.popMax();
    	Data min_data = Q.bottom(); Q.popMin();
    	printf("(%d, %d)\n", max_data.value1, max_data.value2);
    	printf("(%d, %d)\n", min_data.value1, min_data.value2);
    	printf("\n");
    }

    return 0;
}
#endif
```
