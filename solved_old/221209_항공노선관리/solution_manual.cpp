#if 1
// Manual 813 ms: Array + Linked List + Priority Queue
//#include <queue>
//#include <vector>
//using namespace std;

#define NUM_AIRPORTS	60
#define INF		2147483647	// INT32_MAX

template<typename Type>
struct LinkedList {
    struct List {
        Type data;
        List* next;
    };
    List* head;
    List* tail;

    void push_back(const Type& data) {
        List* node = new List({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Airline {
    int to;
    int start_time;
    int travel_time;
    int price;
};

LinkedList<Airline> airlines[NUM_AIRPORTS];
int airportCnt;

struct TimeData {
    int to;
    int time;
    bool operator<(const TimeData& data) const { return time > data.time; }
};

struct PriceData {
    int to;
    int price;
    bool operator<(const PriceData& data) const { return price > data.price; }
};

#if 0
template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue {
    Type heap[NUM_AIRPORTS*10];
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
};
#endif

/////////////////////////////////////////////////////////////////
void init(int N)
{
    for (int i = 0; i < N; i++) { airlines[i] = {}; }
    airportCnt = N;
}

// 3¸¸¹ø
void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
    airlines[mStartAirport].push_back({ mEndAirport, mStartTime, mTravelTime, mPrice });
}

// 1,000
int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
    int ret = -1;
    PriorityQueue<TimeData> Q;
    int cost[NUM_AIRPORTS];
    for (int i = 0; i < airportCnt; i++) { cost[i] = INF; }

    Q.push({ mStartAirport, mStartTime });
    cost[mStartAirport] = mStartTime;

    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();
        int cur_to = data.to, cur_time = data.time;

        if (cur_to != mStartAirport && cur_to == mEndAirport) {
            ret = cur_time - mStartTime;
            break;
        }
        if (cur_time > cost[cur_to]) continue;

        for (auto ptr = airlines[cur_to].head; ptr; ptr = ptr->next) {
            auto next = ptr->data;
            cur_time %= 24;
            int wait_time;

            if (cur_time > next.start_time)
                wait_time = 24 - (cur_time - next.start_time);
            else
                wait_time = next.start_time - cur_time;

            if (cost[next.to] > cost[cur_to] + wait_time + next.travel_time) {
                cost[next.to] = cost[cur_to] + wait_time + next.travel_time;
                Q.push({ next.to, cost[next.to] });
            }
        }
    }
    return ret;
}

// 5,000
int minPrice(int mStartAirport, int mEndAirport)
{
    int ret = -1;
    PriorityQueue<PriceData> Q;
    int cost[NUM_AIRPORTS];
    for (int i = 0; i < airportCnt; i++) { cost[i] = INF; }

    Q.push({ mStartAirport, 0 });
    cost[mStartAirport] = 0;

    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();
        int cur_to = data.to, cur_price = data.price;

        if (cur_to != mStartAirport && cur_to == mEndAirport) {
            ret = cur_price;
            break;
        }
        if (cur_price > cost[cur_to]) continue;

        for (auto ptr = airlines[cur_to].head; ptr; ptr = ptr->next) {
            auto next = ptr->data;
            if (cost[next.to] > cost[cur_to] + next.price) {
                cost[next.to] = cost[cur_to] + next.price;
                Q.push({ next.to, cost[next.to] });
            }
        }
    }
    return ret;
}
#endif