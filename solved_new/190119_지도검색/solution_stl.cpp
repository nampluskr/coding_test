#if 1
#include <vector>
#include <queue>
using namespace std;

#define MAX_FACILITIES  (50000 + 1)
#define MAX_TYPES       (10 + 1)
#define MAX_N           100         // num. of partitions = sqrt(10000)
#define ADDED           0
#define REMOVED         1

struct Facility {
    int mId, mType, mY, mX, state;
    int dist(int mY, int mX) { 
        return (this->mY - mY) * (this->mY - mY) + (this->mX - mX) * (this->mX - mX);
    }
};

Facility facilities[MAX_FACILITIES];
vector<int> facilityList[MAX_TYPES];
vector<int> buckets[MAX_TYPES][MAX_N][MAX_N];

int N;              // bucket size
int num_buckets;

struct Data {
    int dist, mId;
    bool operator<(const Data& data) const {
        return (dist > data.dist) || (dist == data.dist && mId > data.mId);
    }
};

////////////////////////////////////////////////////////////////////
void init(int n)
{
    N = sqrt(n);
    num_buckets = ceil((double)n / N);

    for (int i = 0; i < MAX_FACILITIES; i++) { facilities[i] = {}; }

    for (int i = 0; i < MAX_TYPES; i++) { 
        facilityList[i].clear();
        for (int j = 0; j < num_buckets; j++)
            for (int k = 0; k < num_buckets; k++) {
                buckets[i][j][k].clear();
            }
    }
}

void addFacility(int mId, int mType, int mY, int mX) 
{
    facilities[mId] = { mId, mType, mY, mX, ADDED };

    facilityList[mType].push_back(mId);
    facilityList[0].push_back(mId);

    buckets[mType][(mY - 1) / N][(mX - 1) / N].push_back(mId);
    buckets[0][(mY - 1) / N][(mX - 1) / N].push_back(mId);
}

void removeFacility(int mId) 
{
    facilities[mId].state = REMOVED;
}

int search1(int mType, int mY, int mX, int mRadius) 
{ 
    // ÀüÃ¼ Å½»ö
    //int ret = 0;
    //for (int mId : facilityList[mType]) {
    //    if (facilities[mId].state == REMOVED) continue;
    //    if (facilities[mId].dist(mY, mX) <= mRadius * mRadius) { ret += 1; }
    //}

    // ºÎºÐ Å½»ö
    int sY = max((mY - 1 - mRadius) / N, 0);
    int eY = min((mY - 1 + mRadius) / N, num_buckets - 1);
    int sX = max((mX - 1 - mRadius) / N, 0);
    int eX = min((mX - 1 + mRadius) / N, num_buckets - 1);

    int ret = 0;
    for (int i = sY; i <= eY; i++)
        for (int j = sX; j <= eX; j++)
            for (int mId: buckets[mType][i][j]) {
                if (facilities[mId].state == REMOVED) continue;
                if (facilities[mId].dist(mY, mX) <= mRadius * mRadius) { ret += 1; }
            }
    return ret;
}

void search2(int mType, int mY, int mX, int mIdList[5]) 
{
    priority_queue<Data> Q;

    for (int mId: facilityList[mType]) {
        if (facilities[mId].state == REMOVED) continue;
        Q.push({ facilities[mId].dist(mY, mX), mId });
    }

    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto data = Q.top(); Q.pop();
        mIdList[cnt++] = data.mId;
    }
}
#endif