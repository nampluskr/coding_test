#if 1
// STL xxx ms
#include <vector>
using namespace std;

struct Data {
    int x;
    int dist;
};

struct Node {
    int mID;
    int parent;
    int quantity;
    int total;
    int depth;
    int distance;
    vector<int> childList;
};
vector<Node> nodes;

//////////////////////////////////////////////////////////////////////////////
int get_LCA(int x, int y) {
    if (nodes[x].depth < nodes[y].depth)
        swap(x, y);

    while (nodes[x].depth != nodes[y].depth) {
        x = nodes[x].parent;
    }
    while (x != y) {
        x = nodes[x].parent;
        y = nodes[y].parent;
    }
    return x;
}

void update_parents(int mIdx, int quantity) {
    int pIdx = nodes[mIdx].parent;
    while (pIdx != -1) {
        nodes[pIdx].total += quantity;
        pIdx = nodes[pIdx].parent;
    }
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mParent[], int mDistance[], int mQuantity[])
{
    nodes.clear();  nodes.resize(N);

    nodes[0].mID = 0;
    nodes[0].parent = mParent[0];
    nodes[0].quantity = mQuantity[0];
    nodes[0].total += mQuantity[0];

    for (int i = 1; i < N; i++) {
        nodes[i].mID = i;
        nodes[i].parent = mParent[i];
        nodes[i].quantity = mQuantity[i];
        nodes[i].total += mQuantity[i];
        nodes[i].depth = nodes[mParent[i]].depth + 1;
        nodes[i].distance = nodes[mParent[i]].distance + mDistance[i];

        nodes[i].childList.push_back(mParent[i]);
        nodes[mParent[i]].childList.push_back(i);

        update_parents(i, mQuantity[i]);
    }
}

// LCA
int carry(int mFrom, int mTo, int mQuantity)
{
    nodes[mFrom].quantity -= mQuantity;
    nodes[mTo].quantity += mQuantity;

    update_parents(mFrom, -mQuantity);
    update_parents(mTo, mQuantity);

    int lca = get_LCA(mFrom, mTo);
    int distance = nodes[mFrom].distance + nodes[mTo].distance - nodes[lca].distance * 2;
    int ret = distance * mQuantity;

    return ret;
}

int gather(int mID, int mQuantity)
{
    return 0;
}

int sum(int mID)
{
    int ret = nodes[mID].total;
    return ret;
}
#endif
