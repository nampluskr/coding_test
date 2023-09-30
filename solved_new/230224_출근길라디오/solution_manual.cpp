#if 1
// STL Brute Force 7357 ms / STL 830 ms / Manual 705 ms
#include <cmath>    // sqrt, ceil

void swap(int& a, int& b) { int temp = b; b = a; a = temp; }

#define MAX_ROADS   100000      // from 0 ~ 99999
#define MAX_TYPES   1000        // from 0 ~ 999

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Type {
    LinkedList<int> roadList;
};
Type types[MAX_TYPES];

int num_values;
int bucket_size;
int num_buckets;

struct Partition {
    int buckets[MAX_ROADS]; // sum of mTime for a bucket
    int values[MAX_ROADS];  // mTime value
    int N;                  // bucket size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_buckets; i++) { buckets[i] = 0; }
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
    }
    void update(int idx, int value) {
        buckets[idx / N] -= values[idx];
        values[idx] = value;
        buckets[idx / N] += value;
    }
    int query(int idx) { return values[idx]; }
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
        for (int i = s + 1; i <= e - 1; i++) {
            ret += buckets[i];
        }
        return ret;
    }
};
Partition part;

/////////////////////////////////////////////////////////////////////
void init(int N, int M, int mType[], int mTime[])
{
    for (int i = 0; i < M; i++) { types[i].roadList.clear(); }

    num_values = N - 1;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();

    for (int i = 0; i < N - 1; i++) {
        types[mType[i]].roadList.push_back(i);
        part.update(i, mTime[i]);
    }
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
        int mID = node->data;
        int new_time = part.query(mID) * mRatio256 / 256;
        part.update(mID, new_time);
        ret += new_time;
    }
    return ret;
}

// 100,000
int calculate(int mA, int mB)
{
    int ret = 0;
    if (mA > mB) { swap(mA, mB); }

    ret = part.query(mA, mB - 1);
    return ret;
}
#endif