#if 0
// STL Brute Force 7357 ms / STL 830 ms
#include <vector>
using namespace std;

struct Type {
    vector<int> roadList;
};
vector<Type> types;

int num_values;
int bucket_size;
int num_buckets;

struct Partition {
    vector<int> buckets;    // sum of mTime for a bucket
    vector<int> values;     // mTime value
    int N;                  // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
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
    types.clear();  types.resize(M);

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
    for (int mID : types[mTypeID].roadList) {
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