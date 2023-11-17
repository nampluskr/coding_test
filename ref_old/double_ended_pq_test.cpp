#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_LEN 12

using ull = unsigned long long;
#define MAX_ENCODING    4
#define ALPHA       1111 // 2^32 * (sqrt(5) - 1) / 2
#define MAX_TABLE   1024

ull encode(const char str[]) {
    ull hashkey = 0;
    int i = 0;
    for (; str[i]; i++) { hashkey = hashkey * 27 + str[i] - 'a' + 1; }
    for (; i < MAX_ENCODING; i++) { hashkey *= 27; }
    return hashkey;
}

void decode(char str[], ull hashkey) {
    int i = MAX_ENCODING;
    for (; hashkey % 27 == 0; i--) { hashkey /= 27; }
    str[i--] = '\0';
    for (; hashkey > 0; i--) { str[i] = hashkey % 27 + 'a' - 1; hashkey /= 27; }
}

int intHash(ull key) {
    ull hashkey = key * ALPHA;
    return hashkey & (MAX_TABLE - 1);
}

int strHash(const char key[]) {
    ull hashkey = 5381;
    int c;
    while (c = *key++) { hashkey = (((hashkey << 5) + hashkey) + c) % MAX_TABLE; }
    return hashkey % MAX_TABLE;
}

struct Data {
    char name[MAX_LEN];
    int value;
    bool operator<(const Data& data) const { return strcmp(name, data.name) < 0; }
};

template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void clear() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};

template<typename Type>
struct DoubleEndedPQ {
    struct MinData {
        Type data;
        int idx;
        bool operator<(const MinData& d) const { return !(data < d.data); }
    };
    struct MaxData {
        Type data;
        int idx;
        bool operator<(const MaxData& d) const { return data < d.data; }
    };
    PriorityQueue<MinData> minHeap;
    PriorityQueue<MaxData> maxHeap;
    vector<bool> isPopped;
    int idx = 0;
    int heapSize = 0;

    void clear() { minHeap.clear(); maxHeap.clear(); isPopped.clear();  heapSize = 0; idx = 0; }
    void push(const Type& data) {
        minHeap.push({ data, idx });
        maxHeap.push({ data, idx });
        isPopped.push_back(false);
        idx += 1;
        heapSize += 1;
    }
    void popMin() {
        while (!minHeap.empty() && isPopped[minHeap.top().idx]) { minHeap.pop(); }
        isPopped[minHeap.top().idx] = true;
        minHeap.pop();
        heapSize -= 1;
    }
    void popMax() {
        while (!maxHeap.empty() && isPopped[maxHeap.top().idx]) { maxHeap.pop(); }
        isPopped[maxHeap.top().idx] = true;
        maxHeap.pop();
        heapSize -= 1;
    }
    Type Bottom() {
        while (!minHeap.empty() && isPopped[minHeap.top().idx]) { minHeap.pop(); }
        return minHeap.top().data;
    }
    Type top() {
        while (!maxHeap.empty() && isPopped[maxHeap.top().idx]) { maxHeap.pop(); }
        return maxHeap.top().data;
    }
    bool empty() { return heapSize == 0; }
};
DoubleEndedPQ<Data> Q;

int main()
{
    Q.clear();

    Q.push({ "aaa", 20});
    Q.push({ "bbb", 30});
    Q.push({ "ccc", 30});
    Q.push({ "ddd", 30});
    Q.push({ "eee", 30});
    Q.push({ "fff", 30});

    Q.popMax();
    Q.popMin();
    return 0;
}
