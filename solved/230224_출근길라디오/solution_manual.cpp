#if 1
// Manual 635 ms / STL 679 ms / Brute Force 1176 ms
#define NUM_ROADS   100000
#define NUM_TYPES   1000

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    void init() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Road {
    int time;
    int type;
};
Road roads[NUM_ROADS];

struct Type {
    LinkedList<int> roadList;
};
Type types[NUM_TYPES];

//////////////////////////////////////////////////////////////////////////
inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

//////////////////////////////////////////////////////////////////////////
#define NUM_VALUES  NUM_ROADS
#define BUCKET_SIZE 316         // sqrt(NUM_ROADS)
#define NUM_BUCKETS 317         // ceil((double)NUM_ROADS / BUCKET_SIZE)

struct Partition {
    int values[NUM_VALUES];
    int buckets[NUM_BUCKETS];
    int N;    // bucket size

    void init(int num_values) {
        N = BUCKET_SIZE;
        for (int i = 0; i < NUM_BUCKETS; i++) { buckets[i] = {}; }
        for (int i = 0; i < NUM_VALUES; i++) { values[i] = {}; }

        // 초기화
        for (int i = 0; i < num_values; i++) {
            values[i] = roads[i].time;
            buckets[i / N] += roads[i].time;
        }
    }
    void update(int idx, int value) {
        buckets[idx / N] -= values[idx];
        values[idx] = value;
        buckets[idx / N] += value;
    }
    int query(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret += values[i]; }
            return ret;
        }
        while (left / N == s) { ret += values[left++]; }
        while (right / N == e) { ret += values[right--]; }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i]; }

        return ret;
    }
};
Partition part;

//////////////////////////////////////////////////////////////////////////
void init(int N, int M, int mType[], int mTime[])
{
    for (int i = 0; i < NUM_ROADS; i++) { roads[i] = {}; }
    for (int i = 0; i < NUM_TYPES; i++) { types[i] = {}; }

    for (int i = 0; i < N - 1; i++) {
        roads[i].type = mType[i];
        roads[i].time = mTime[i];
        types[mType[i]].roadList.push_back(i);
    }
    part.init(N - 1);
}

void destroy() {}

void update(int mID, int mNewTime)
{
    roads[mID].time = mNewTime;
    part.update(mID, mNewTime);
}

int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;
    for (auto ptr = types[mTypeID].roadList.head; ptr; ptr = ptr->next) {
        int rIdx = ptr->data;
        int temp = roads[rIdx].time * mRatio256 / 256;
        roads[rIdx].time = temp;
        part.update(rIdx, temp);
        ret += roads[rIdx].time;
    }
    return ret;
}

int calculate(int mA, int mB)
{
    int ret = 0;
    if (mA > mB) { swap(mA, mB); }

    //for (int i = mA; i < mB; i++) { ret += roads[i].time; }
    ret = part.query(mA, mB - 1);
    return ret;
}
#endif