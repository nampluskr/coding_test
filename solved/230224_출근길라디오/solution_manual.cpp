#if 1
// Manual 717 ms: Partition (Point update + Range query)
// Array, Linked List
#define NUM_ROADS 100000
#define NUM_TYPES 1000

#define BUCKET_SIZE     316     // sqrt(NUM_ROADS)
#define NUM_BUCKETS     317     // ceil((double)NUM_ROADS / NUM_BUCKETS)

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

struct LinkedList {
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;

    void init() { head = nullptr; tail = nullptr; }
    void push_back(int value) {
        Node* node = new Node({ value, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Road {
    int time;
    int type;
};
Road roads[NUM_ROADS];
int roadCnt;

struct Type {
    LinkedList roadList;
};
Type types[NUM_TYPES];

//////////////////////////////////////////////////////////////////////////
struct Partition {
    int buckets[NUM_BUCKETS];
    int N;    // bucket size

    void init() {
        N = BUCKET_SIZE;
        for (int i = 0; i < NUM_BUCKETS; i++) { buckets[i] = 0; }
        for (int i = 0; i < roadCnt; i++) { buckets[i / N] += roads[i].time; }
    }
    void update(int idx, int value) {
        buckets[idx / N] -= roads[idx].time;
        roads[idx].time = value;
        buckets[idx / N] += value;
    }
    int query(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret += roads[i].time; }
            return ret;
        }
        while (left / N == s) { ret += roads[left++].time; }
        while (right / N == e) { ret += roads[right--].time; }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i]; }

        return ret;
    }
};
Partition part;

//////////////////////////////////////////////////////////////////////////
// N: 지점의 개수(10 ≤ N ≤ 100,000)
// M : 도로의 종류(1 ≤ M ≤ 1,000)
void init(int N, int M, int mType[], int mTime[])
{
    roadCnt = N - 1;
    for (int i = 0; i < N - 1; i++) { roads[i] = { 0, 0 }; }
    for (int i = 0; i < M; i++) { types[i].roadList.init(); }

    for (int i = 0; i < N - 1; i++) {
        roads[i].type = mType[i];
        roads[i].time = mTime[i];
        types[mType[i]].roadList.push_back(i);
    }
    part.init();
}

void destroy() {}

// 10,000
void update(int mID, int mNewTime)
{
    part.update(mID, mNewTime);
}

// 200
int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;
    for (auto node = types[mTypeID].roadList.head; node; node = node->next) {
        int rIdx = node->value;
        int temp = roads[rIdx].time * mRatio256 / 256;
        part.update(rIdx, temp);
        ret += roads[rIdx].time;
    }
    return ret;
}

// 100,000
int calculate(int mA, int mB)
{
    if (mA > mB) { swap(mA, mB); }

    return part.query(mA, mB - 1);
}
#endif