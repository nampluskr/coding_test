#if 0
// STL Brute Force 7357 ms
#include <vector>
using namespace std;

struct Road {
    int mType;
    int mTime;
};
vector<Road> roads;

struct Type {
    vector<int> roadList;
};
vector<Type> types;

/////////////////////////////////////////////////////////////////////
void init(int N, int M, int mType[], int mTime[])
{
    roads.clear();  roads.resize(N - 1);
    types.clear();  types.resize(M);

    for (int i = 0; i < N - 1; i++) {
        roads[i] = { mType[i], mTime[i] };
        types[mType[i]].roadList.push_back(i);
    }
}

void destroy() {}

// 10,000
void update(int mID, int mNewTime)
{
    roads[mID].mTime = mNewTime;
}

// 200
int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;
    for (int mID : types[mTypeID].roadList) {
        roads[mID].mTime = roads[mID].mTime * mRatio256 / 256;
        ret += roads[mID].mTime;
    }
    return ret;
}

// 100,000
int calculate(int mA, int mB)
{
    int ret = 0;
    if (mA > mB) { swap(mA, mB); }
    for (int mID = mA; mID < mB; mID++) {
        ret += roads[mID].mTime;
    }
    return ret;
}
#endif