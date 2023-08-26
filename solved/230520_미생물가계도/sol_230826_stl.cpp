#if 0
// STL 1058 ms
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

#define NUM_NODES   (12000 + 1)
#define NUM_DAYS    (1000000 + 1)

struct Node {
    int parent;
    int depth;
    int first_day;
    int last_day;
};
vector<Node> nodes;
int nodeCnt;
unordered_map<string, int> nodeMap;

//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(const char mName[]) {
    int nIdx;
    auto ptr = nodeMap.find(string(mName));
    if (ptr == nodeMap.end()) {
        nIdx = nodeCnt;
        nodeMap.emplace(string(mName), nIdx);
        nodeCnt += 1;
    }
    else { nIdx = ptr->second; }
    return nIdx;
}

int get_lca(int x, int y) {
    if (nodes[x].depth < nodes[y].depth) { swap(x, y); }

    while (nodes[x].depth != nodes[y].depth) {
        x = nodes[x].parent;
    }
    while (x != y) {
        x = nodes[x].parent;
        y = nodes[y].parent;
    }
    return x;
}

struct Partition {
    vector<int> buckets;
    vector<int> values;
    int N;      // bucket size

    void init(int num_values) {
        N = sqrt(num_values);
        int num_buckets = ceil((double)num_values / N);
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
    int query(int idx) {
        int ret = buckets[idx / N] + values[idx];
        return ret;
    }
};
Partition part;

//////////////////////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    nodes.clear();  nodes.resize(NUM_NODES);
    nodeCnt = 0;
    nodeMap.clear();

    int nIdx = get_nodeIndex(mAncestor);
    nodes[nIdx] = { -1, 0, 0, mLastday };
    
    part.init(NUM_DAYS);
    part.update(0, mLastday, 1);
}

int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int nIdx = get_nodeIndex(mName);
    int pIdx = get_nodeIndex(mParent);

    nodes[nIdx].parent = pIdx;
    nodes[nIdx].depth = nodes[pIdx].depth + 1;
    nodes[nIdx].first_day = mFirstday;
    nodes[nIdx].last_day = mLastday;

    part.update(mFirstday, mLastday, 1);

    return nodes[nIdx].depth;
}

int distance(char mName1[], char mName2[])
{
    int x = get_nodeIndex(mName1);
    int y = get_nodeIndex(mName2);

    int lca = get_lca(x, y);
    int ret = nodes[x].depth + nodes[y].depth - 2 * nodes[lca].depth;
    return ret;
}

int count(int mDay)
{
    int ret = part.query(mDay);
    return ret;
}
#endif