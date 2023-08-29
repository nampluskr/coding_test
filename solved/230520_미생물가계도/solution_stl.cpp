#if 0
// STL 1135 ms
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

#define NUM_NODES   12001
#define NUM_VALUES  1000001

struct Node {
    int parent;
    int depth;
    int firstDay;
    int lastDay;
};
unordered_map<string, int> nodeMap;
vector<Node> nodes;
int nodeCnt;

struct Partition {
    vector<int> buckets;
    vector<int> values;
    int N;        // bucket size;

    void init() {
        N = sqrt(NUM_VALUES);
        int num_buckets = ceil((double)NUM_VALUES / N);
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();        values.resize(NUM_VALUES);
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { values[i] += 1; }
            return;
        }
        while (left / N == s) { values[left++] += 1; }
        while (right / N == e) { values[right--] += 1; }
        for (int i = s + 1; i <= e - 1; i++) { buckets[i] += 1; }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N];
    }
};
Partition part;

//////////////////////////////////////////////////////////////
int get_nodeIndex(char mName[]) {
    int nIdx;
    auto pos = nodeMap.find(string(mName));
    if (pos == nodeMap.end()) {
        nIdx = nodeCnt;
        nodeMap[string(mName)] = nIdx;
        nodeCnt += 1;
    }
    else { nIdx = pos->second; }
    return nIdx;
}

//////////////////////////////////////////////////////////////
int get_LCA(int x, int y) {
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
//////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    nodeMap.clear();
    nodes.clear();    nodes.resize(NUM_NODES);
    nodeCnt = 0;

    int nIdx = get_nodeIndex(mAncestor);
    nodes[nIdx] = { -1, 0, 0, mLastday };

    part.init();
    part.update(0, mLastday, 1);
}

// 12,000
int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int nIdx = get_nodeIndex(mName);
    int pIdx = get_nodeIndex(mParent);

    nodes[nIdx] = { pIdx, nodes[pIdx].depth + 1, mFirstday, mLastday };
    part.update(mFirstday, mLastday, 1);
    return nodes[nIdx].depth;
}

// 50,000
int distance(char mName1[], char mName2[])
{
    int x = get_nodeIndex(mName1);
    int y = get_nodeIndex(mName2);
    int lca = get_LCA(x, y);
    int ret = nodes[x].depth + nodes[y].depth - 2 * nodes[lca].depth;
    return ret;
}

// 2,000
int count(int mDay)
{
    return part.query(mDay);
}
#endif
