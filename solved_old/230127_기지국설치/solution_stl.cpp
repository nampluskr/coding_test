#if 1
// STL 1135 ms
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define NUM_BUILDINGS   24000
#define ADDED       0
#define DELETED     1

struct Building {
    int ID;
    int location;
    int state;
};

unordered_map<int, int> bldgMap;
vector<Building> bldg;
int bldgCnt;
int deleteCnt;

//////////////////////////////////////////////////////////////////////////////
int get_bldgIndex(int mId) {
    int bIdx;
    auto ptr = bldgMap.find(mId);
    if (ptr == bldgMap.end()) {
        bIdx = bldgCnt;
        bldgMap[mId] = bIdx;
        bldgCnt += 1;
    }
    else { bIdx = ptr->second; }
    return bIdx;
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mId[], int mLocation[])
{
    bldgMap.clear();
    bldg.clear();  bldg.resize(NUM_BUILDINGS);
    bldgCnt = 0;
    deleteCnt = 0;

    for (int i = 0; i < N; i++) {
        int bIdx = get_bldgIndex(mId[i]);
        bldg[bIdx] = { mId[i], mLocation[i], ADDED };
    }
}

// 24,000
int add(int mId, int mLocation)
{
    int bIdx = get_bldgIndex(mId);
    if (bldg[bIdx].state == DELETED) {
        deleteCnt -= 1;
    }
    bldg[bIdx] = { mId, mLocation, ADDED };
    return bldgCnt - deleteCnt;
}

// 3,000
int remove(int mStart, int mEnd)
{
    for (int i = 0; i < bldgCnt; i++) {
        if (bldg[i].location >= mStart && bldg[i].location <= mEnd)
            if (bldg[i].state != DELETED) {
                bldg[i].state = DELETED;
                deleteCnt += 1;
            }
    }
    return bldgCnt - deleteCnt;
}

int install(int M)
{
    vector<int> loc;
    for (int i = 0; i < bldgCnt; i++) {
        if (bldg[i].state != DELETED)
            loc.push_back(bldg[i].location);
    }
    sort(loc.begin(), loc.end());

    int ret = 0;
    int start = 1;
    int end = loc.back() - loc.front();

    while (start <= end) {
        int mid = (start + end) / 2;
        int cnt = 1;
        int cur = loc[0];

        for (int i = 1; i < loc.size(); ++i) {
            if (loc[i] - cur >= mid) {
                cnt += 1;
                cur = loc[i];
            }
        }
        if (cnt >= M) {
            ret = max(ret, mid);
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return ret;
}
#endif