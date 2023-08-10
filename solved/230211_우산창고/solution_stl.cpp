#if 0
// STL 103 ms (WS)
#include <vector>
#include <queue>
using namespace std;

struct Data {
    int x;
    int dist;

    bool operator<(const Data& data) const {
        return (dist > data.dist) || (dist== data.dist && x > data.x);
    }
};
struct Node {
    int mID;
    int parent;             // 부모 노드
    int depth;              // 루트로부터 누적 깊이
    int distance;           // 루트로부터 누적 거리

    int quantity;           // 우산 개수
    int total;              // 자기 + 하위 노드 누적 개수
    vector<Data> childList; // 인접 리스트: {연결 노드, 거리}

    void update_quantity(int mQuantity) {
        quantity += mQuantity;
        total += mQuantity;
    }
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
    nodes[0].update_quantity(mQuantity[0]);

    for (int i = 1; i < N; i++) {
        nodes[i].mID = i;
        nodes[i].parent = mParent[i];
        nodes[i].depth = nodes[mParent[i]].depth + 1;
        nodes[i].distance = nodes[mParent[i]].distance + mDistance[i];

        nodes[i].update_quantity(mQuantity[i]);
        update_parents(i, mQuantity[i]);

        nodes[i].childList.push_back({ mParent[i], mDistance[i]});
        nodes[mParent[i]].childList.push_back({ i, mDistance[i] });
    }
}

int carry(int mFrom, int mTo, int mQuantity)
{
    nodes[mFrom].update_quantity(-mQuantity);
    update_parents(mFrom, -mQuantity);

    nodes[mTo].update_quantity(+mQuantity);
    update_parents(mTo, mQuantity);

    int lca = get_LCA(mFrom, mTo);
    int distance = nodes[mFrom].distance + nodes[mTo].distance - nodes[lca].distance * 2;
    int ret = distance * mQuantity;
    return ret;
}

int gather(int mID, int mQuantity)
{
    priority_queue<Data> Q;
    vector<bool> visited(nodes.size());
    int ret = 0;

    visited[mID] = true;
    Q.push({ mID, 0 });
    while (!Q.empty() && mQuantity > 0) {
        auto node = Q.top(); Q.pop();

        if (node.x != mID) {
            int quantity = min(mQuantity, nodes[node.x].quantity);
            ret += carry(node.x, mID, quantity);
            mQuantity -= quantity;
        }
        for (const auto& next : nodes[node.x].childList) {
            if (!visited[next.x]) {
                visited[next.x] = true;
                int lca = get_LCA(next.x, mID);
                int dist = nodes[next.x].distance + nodes[mID].distance - nodes[lca].distance * 2;
                Q.push({ next.x, dist});
            }
        }
    }
    return ret;
}

int sum(int mID)
{
    int ret = nodes[mID].total;
    return ret;
}
#endif
