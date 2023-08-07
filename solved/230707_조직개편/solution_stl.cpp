#include <vector>
#include <unordered_map>
using namespace std;

#define NUM_NODES   8000
#define DELETED     1

struct Node{
    int mId;
    int num;
    int parent;
    int state;

    int num_children;
    vector<int> childList;
};
unordered_map<int, int> nodeMap;
vector<Node>nodes;
int nodeCnt;

//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(int mId) {
    int nIdx;
    auto ptr = nodeMap.find(mId);
    if (ptr == nodeMap.end()) {
        nIdx = nodeCnt;
        nodeMap[mId] = nIdx;
        nodeCnt += 1;
    }
    else {
        nIdx = ptr->second;
        if (nodes[nIdx].state == DELETED) { nIdx = -1; }
    }
    return nIdx;
}

void update_parents(int nIdx, int mNum) {
    int pIdx = nodes[nIdx].parent;
    while (pIdx != -1) {
        nodes[pIdx].num += mNum;
        pIdx = nodes[pIdx].parent;
    }
}
// dfs
void remove_children(int x) {
    nodes[x].state = DELETED;
    for (int child: nodes[x].childList)
        if (nodes[child].state != DELETED) {
            remove_children(child);
        }
}
//////////////////////////////////////////////////////////////////////////////
void init(int mId, int mNum)
{
    nodeMap.clear();
    nodes.clear();  nodes.resize(NUM_NODES);
    nodeCnt = 0;

    int nIdx = get_nodeIndex(mId);
    nodes[nIdx].mId = mId;
    nodes[nIdx].num = mNum;
    nodes[nIdx].parent = -1;
}

int add(int mId, int mNum, int mParent)
{
    int ret = -1;
    int nIdx = get_nodeIndex(mId);
    int pIdx = get_nodeIndex(mParent);

    if (nodes[pIdx].num_children < 2) {
        nodes[pIdx].num_children += 1;
        nodes[pIdx].childList.push_back(nIdx);

        nodes[nIdx].mId = mId;
        nodes[nIdx].num = mNum;
        nodes[nIdx].parent = pIdx;

        update_parents(nIdx, mNum);
        ret = nodes[pIdx].num;
    }
    else { nodes[nIdx].state = DELETED; }
    return ret;
}

// 1,000
int remove(int mId)
{
    int ret = -1;
    int nIdx = get_nodeIndex(mId);

    if (nIdx != -1) {
        remove_children(nIdx);
        update_parents(nIdx, -nodes[nIdx].num);
        nodes[nodes[nIdx].parent].num_children -= 1;
        ret = nodes[nIdx].num;
    }
    return ret;
}

// 1,000
int reorganize(int M, int K) {
    return 0;
}