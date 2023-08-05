#if 1
// 1. array 585 ms
// 2. Linked List 614 ms
// 3. PriorityQueue 410 ms
//#include <vector>
//#include <queue>
//using namespace std;

#define INF         2147483647  // INT32_MAX
#define NUM_HOTELS  5000
#define NUM_BRANDS  50

template<typename Type>
struct LinkedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;

    void clear() { head = nullptr; tail = nullptr; size = 0; };
    void push_back(const Type& data) {
        Node* node = new Node({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        size += 1;
    }
};

struct Hotel {
    int brand;
};
Hotel hotels[NUM_HOTELS];

struct Brand {
    LinkedList<int> hotelList;
};
Brand brands[NUM_BRANDS];

struct Data {
    int x;
    int dist;
    bool operator<(const Data& data) const { return dist > data.dist; }
};
LinkedList<Data> graph[NUM_HOTELS];
int dist[NUM_HOTELS];            // dist[x] start ~ x 까지 거리

#if 0
struct PriorityQueue {
    priority_queue<Data> heap;
    int heapSize = 0;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Data& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Data top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue {
    Type heap[NUM_HOTELS];
    int heapSize = 0;

    void init() { heapSize = 0; }
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

        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[current] < heap[child]) {
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
};

#endif

///////////////////////////////////////////////////////////////////////////////
int dijkstra(int start, int brand, int visited) {
    PriorityQueue<Data> Q;
    for (int i = 0; i < NUM_HOTELS; i++) { dist[i] = INF; }

    Q.push({ start, 0 });
    while (!Q.empty()) {
        auto node = Q.top(); Q.pop();   // x, dist

        if (node.x != start && hotels[node.x].brand == brand && node.x != visited) {
            return node.x;
        }
        if (dist[node.x] < node.dist) continue;

        for (auto ptr = graph[node.x].head; ptr; ptr = ptr->next) {
            auto next = ptr->data;
            if (dist[next.x] > next.dist + node.dist) {
                dist[next.x] = next.dist + node.dist;
                Q.push({ next.x, dist[next.x] });
            }
        }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////
void init(int N, int mBrands[])
{
    for (int i = 0; i < NUM_HOTELS; i++) { hotels[i].brand = 0; }
    for (int i = 0; i < NUM_BRANDS; i++) { brands[i].hotelList.clear(); }

    for (int i = 0; i < N; i++) {
        hotels[i].brand = mBrands[i];
        brands[mBrands[i]].hotelList.push_back(i);
    }

    for (int i = 0; i < NUM_HOTELS; i++) {
        graph[i].clear();
        dist[i] = 0;
    }
}

// 10,000
void connect(int mHotelA, int mHotelB, int mDistance)
{
    graph[mHotelA].push_back({ mHotelB, mDistance });
    graph[mHotelB].push_back({ mHotelA, mDistance });
}

// 100
int merge(int mHotelA, int mHotelB)
{
    int brandA = hotels[mHotelA].brand;
    int brandB = hotels[mHotelB].brand;

    if (brandA != brandB) {
        for (auto node = brands[brandB].hotelList.head; node; node = node->next) {
            auto hotelB = node->data;
            hotels[hotelB].brand = brandA;
            brands[brandA].hotelList.push_back(hotelB);
        }
    }
    return brands[brandA].hotelList.size;
}

// 1,000
int move(int mStart, int mBrandA, int mBrandB)
{
    int hotelA = dijkstra(mStart, mBrandA, mStart);
    int distA = dist[hotelA];

    int hotelB = dijkstra(mStart, mBrandB, hotelA);
    int distB = dist[hotelB];

    return distA + distB;
}
#endif