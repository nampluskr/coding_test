#if 0
#include <vector>
#include <queue>
using namespace std;

#define MAX_FACILITIES  50001  
#define MAX_TYPES       11
#define REMOVED         1

struct Facility {
    int mType;
    int mY;
    int mX;
    int state;
};
vector<Facility> facilities;
int facilityCnt;

struct Type {
    vector<int> facilityList;
};
vector<Type> types;

struct Data {
    int mId;
    int dist;
    bool operator<(const Data& data) const {
        return (dist > data.dist) || (dist == data.dist && mId > data.mId);
    }
};

//////////////////////////////////////////////////////////////////////////////
int get_dist(const Facility& facility, int mY, int mX) {
    return (facility.mY - mY) * (facility.mY - mY) + (facility.mX - mX) * (facility.mX - mX);
}

//////////////////////////////////////////////////////////////////////////////
void init(int n)
{
    facilities.clear(); facilities.resize(MAX_FACILITIES);
    types.clear();  types.resize(MAX_TYPES);
}

void addFacility(int mId, int mType, int mY, int mX)
{
    facilityCnt = mId;
    facilities[mId] = { mType, mY, mX };

    types[mType].facilityList.push_back(mId);
    types[0].facilityList.push_back(mId);
}

void removeFacility(int mId)
{
    facilities[mId].state = REMOVED;
}

int search1(int mType, int mY, int mX, int mRadius)
{
    int ret = 0;
    for (int mId : types[mType].facilityList) {
        if (facilities[mId].state == REMOVED) continue;

        if (get_dist(facilities[mId], mY, mX) <= mRadius * mRadius) {
            ret += 1;
        }
    }
    return ret;
}

void search2(int mType, int mY, int mX, int mIdList[5])
{
    priority_queue<Data> Q;

    for (int mId : types[mType].facilityList) {
        if (facilities[mId].state == REMOVED) continue;
        Q.push({ mId, get_dist(facilities[mId], mY, mX) });
    }

    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto data = Q.top(); Q.pop();
        mIdList[cnt++] = data.mId;
    }
}
#endif