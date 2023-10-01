#if 0
// STL 633 ms
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;

#define MAX_MICROOBES   12001   // init() + add()
#define MAX_DAYS        1000001 // (0 <= mDay <= 1,000,000)

struct Microbe {
    int parent;
    int depth;
};
vector<Microbe> microbes;
unordered_map<string, int> microbeMap;
int microbeCnt;

int num_values;
int bucket_size;
int num_buckets;

struct Partition {
    vector<int> buckets;    // base (not 구값합)
    vector<int> values;     // 생존 기간
    int N;                  // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { values[i] += value; }
            return;
        }
        while (left / N == s) { values[left++] += value; }
        while (right / N == e) { values[right--] += value; }
        for (int i = s + 1; i <= e - 1; i++) { buckets[i] += value; }
    }
    int query(int idx) { return values[idx] + buckets[idx / N]; }
};
Partition part;

/////////////////////////////////////////////////////////////////////
int get_microbeIndex(const char mName[]) {
    int mIdx;
    auto ret = microbeMap.find(string(mName));
    if (ret == microbeMap.end()) {
        mIdx = microbeCnt++;
        microbeMap.emplace(string(mName), mIdx);
    }
    else { mIdx = ret->second; }
    return mIdx;
}

int get_LCA(int x, int y) {
    if (microbes[x].depth < microbes[y].depth) { swap(x, y); }
    while (microbes[x].depth != microbes[y].depth) {
        x = microbes[x].parent;
    }
    while (x != y) {
        x = microbes[x].parent;
        y = microbes[y].parent;
    }
    return x;
}

/////////////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    microbes.clear();   microbes.resize(MAX_MICROOBES);
    microbeMap.clear();
    microbeCnt = 0;

    int mIdx = get_microbeIndex(mAncestor);
    microbes[mIdx].parent = -1;
    microbes[mIdx].depth = 0;

    num_values = MAX_DAYS;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();
    part.update(0, mLastday, 1);
}

// 12,000
int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int mIdx = get_microbeIndex(mName);
    int pIdx = get_microbeIndex(mParent);
    microbes[mIdx].parent = pIdx;
    microbes[mIdx].depth = microbes[pIdx].depth + 1;

    part.update(mFirstday, mLastday, 1);

    int ret = microbes[mIdx].depth;
    return ret;
}

// 50,000
int distance(char mName1[], char mName2[])
{
    int x = get_microbeIndex(mName1);
    int y = get_microbeIndex(mName2);
    int lca = get_LCA(x, y);

    int ret = microbes[x].depth + microbes[y].depth - 2 * microbes[lca].depth;
    return ret;
}

// 30,000
int count(int mDay)
{
    int ret = part.query(mDay);
    return ret;
}
#endif