#if 1
// STL 559 ms
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX_BUILDINGS   (100 + 24000)
#define ADDED   0
#define REMOVED 1

struct Building {
    int mLocation;
    int state;
};
Building buildings[MAX_BUILDINGS];
int addCnt;
int removeCnt;
unordered_map<int, int> buildingMap;

////////////////////////////////////////////////////////////////////
int get_buildingIndex(int mId) {
    int bIdx;
    auto ret = buildingMap.find(mId);
    if (ret == buildingMap.end()) {
        bIdx = addCnt++;
        buildingMap.emplace(mId, bIdx);
    }
    else { 
        bIdx = ret->second;
        if (buildings[bIdx].state == REMOVED) {
            buildings[bIdx].state = ADDED;
            removeCnt -= 1;
        }
    }
    return bIdx;
}

////////////////////////////////////////////////////////////////////
// N: 건물 개수 ( 2 ≤ N ≤ 100 )
void init(int N, int mId[], int mLocation[])
{
    addCnt = 0;
    removeCnt = 0;
    buildingMap.clear();

    for (int i = 0; i < N; i++) {
        int bIdx = get_buildingIndex(mId[i]);
        buildings[bIdx] = { mLocation[i], ADDED };
    }
}

// 24,000
int add(int mId, int mLocation)
{
    int bIdx = get_buildingIndex(mId);
    buildings[bIdx] = { mLocation, ADDED };

    int ret = addCnt - removeCnt;
    return ret;
}

// 3,000
int remove(int mStart, int mEnd)
{
    for (int i = 0; i < addCnt; i++) {
        if (buildings[i].state == REMOVED) continue;

        if (mStart <= buildings[i].mLocation && buildings[i].mLocation <= mEnd) {
            buildings[i].state = REMOVED;
            removeCnt += 1;
        }
    }
    int ret = addCnt - removeCnt;
    return ret;
}

vector<int> locations;

// [결정문제] 기지국 사이 가장 인접한 거리가 x 일 때, 기지국의 개수는 M 이상인가?
bool condition(int x, int M) {
    int cnt = 1;
    int cur = locations[0];
    for (int i = 1; i < addCnt - removeCnt; i++)
        if (locations[i] - cur >= x) {
            cnt += 1;
            cur = locations[i];
        }
    return cnt >= M;
}

int search(int low, int high, int M) {
    int sol = low;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (condition(mid, M)) {
            sol = mid;
            low = mid + 1;
        }
        else { high = mid - 1; }
    }
    return sol;
}

int install(int M)
{
    locations.clear();
    for (int i = 0; i < addCnt; i++) {
        if (buildings[i].state == REMOVED) continue;
        locations.push_back(buildings[i].mLocation);
    }
    
    sort(locations.begin(), locations.end());
    int low = 1;
    int high = locations[addCnt - removeCnt - 1] - locations[0];
    int ret = search(low, high, M);

    return ret;
}
#endif