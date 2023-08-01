#if 0
// STL 829 ms: Partition (Point update + Range query)
#include <vector>
using namespace std;

struct Road {
    int time;
    int type;
};
vector<Road> roads;
int roadCnt;

struct Type {
    vector<int> roadList;
};
vector<Type> types;

//////////////////////////////////////////////////////////////////////////
struct Partition {
    vector<int> buckets;
    int N;    // bucket size

    void init(int num_values) {
        N = sqrt(num_values);
        int num_buckets = ceil((double)num_values / N);
        buckets.clear(); buckets.resize(num_buckets);

        for (int i = 0; i < num_values; i++) { buckets[i / N] += roads[i].time; }
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
    roadCnt = 0;
    roads.clear();    roads.resize(N - 1);
    types.clear();    types.resize(M);

    for (int i = 0; i < N - 1; i++) {
        roads[i].type = mType[i];
        roads[i].time = mTime[i];
        types[mType[i]].roadList.push_back(i);
    }
    part.init(N - 1);
}

void destroy() {}

// 10,000
void update(int mID, int mNewTime)
{
    //roads[mID].time = mNewTime;
    part.update(mID, mNewTime);
}

// 200
int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;
    for (int rIdx : types[mTypeID].roadList) {
        int temp = roads[rIdx].time * mRatio256 / 256;
        //roads[rIdx].time = temp;
        part.update(rIdx, temp);
        ret += roads[rIdx].time;
    }
    return ret;
}

// 100,000
int calculate(int mA, int mB)
{
    if (mA > mB) { swap(mA, mB); }

    //int ret = 0;
    //for (int rIdx = mA; rIdx < mB; rIdx++) {
    //    ret += roads[rIdx].time;
    //}
    //return ret;

    return part.query(mA, mB - 1);
}
#endif