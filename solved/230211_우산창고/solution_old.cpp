#if 1
// STL 90 ms - 최신 풀이 버젼으로 다시 작성할 것
#include <vector>
#include <queue>
using namespace std;

//inline int min(int x, int y) { return x < y ? x : y; }
//inline int max(int x, int y) { return x > y ? x : y; }
//void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

struct Data {
    int x, dist;

    bool operator<(const Data& data) const {
        return (dist > data.dist) || (dist == data.dist && x > data.x);
    }
};

struct Node {
    int mID;
    int parent;         // 부모 노드
    int depth;          // 루트로부터의 누적 깊이
    int distance;       // 루트로부터의 누적 거리
    int quantity;       // 우산 개수
    int total;          // 자식 노드 우산 개수 누적 (자신 포함)

    //vector<vector<Data>> childList;
};
vector<Node> nodes;

vector<vector<Data>> graph;

/////////////////////////////////////////////////////////
int get_LCA(int x, int y) {
    if (nodes[x].depth < nodes[y].depth)
        swap(x, y);

    while (nodes[x].depth != nodes[y].depth)
        x = nodes[x].parent;

    while (x != y) {
        x = nodes[x].parent;
        y = nodes[y].parent;
    }
    return x;
}

void update_sum_quantity(int mIdx, int quantity) {
    //nodes[mIdx].total += quantity;

    int pIdx = nodes[mIdx].parent;
    while (pIdx != -1) {
        nodes[pIdx].total += quantity;
        pIdx = nodes[pIdx].parent;
    }
}

/////////////////////////////////////////////////////////
void init(int N, int mParent[], int mDistance[], int mQuantity[])
{
    nodes.clear(); nodes.resize(N);
    graph.clear(); graph.resize(N);

    nodes[0].mID = 0;
    nodes[0].parent = -1;
    nodes[0].depth = 0;
    nodes[0].distance = 0;
    nodes[0].quantity = mQuantity[0];
    nodes[0].total = mQuantity[0];

    for (int i = 1; i < N; i++) {
        nodes[i].mID = i;
        nodes[i].parent = mParent[i];
        nodes[i].depth = nodes[nodes[i].parent].depth + 1;
        nodes[i].distance = nodes[nodes[i].parent].distance + mDistance[i];
        nodes[i].quantity = mQuantity[i];

        nodes[i].total += mQuantity[i];
        update_sum_quantity(i, mQuantity[i]);

        // graph
        //nodes[i].childList.push_back({ nodes[i].parent, mDistance[i] });
        //nodes[nodes[i].parent].childList.push_back({ i, mDistance[i] });

        graph[i].push_back({ nodes[i].parent, mDistance[i] });
        graph[nodes[i].parent].push_back({ i, mDistance[i] });
    }
}

// LCA
int carry(int mFrom, int mTo, int mQuantity)
{
    nodes[mFrom].quantity -= mQuantity;
    nodes[mTo].quantity += mQuantity;

    update_sum_quantity(mFrom, -mQuantity);
    update_sum_quantity(mTo, mQuantity);

    int lca = get_LCA(mFrom, mTo);
    int min_distance = nodes[mFrom].distance + nodes[mTo].distance - 2 * nodes[lca].distance;
    int ret = min_distance * mQuantity;
    return ret;
}

// BFS
int gather(int mID, int mQuantity)
{
    priority_queue<Data> Q;
    vector<bool> visited(nodes.size());
    int ret = 0, dist, lca;

    visited[mID] = true;
    Q.push({ mID, 0 });
    while (!Q.empty()) {
        Data node = Q.top(); Q.pop();

        if (node.x != mID) {
            int quantity = min(mQuantity, nodes[node.x].quantity);
            ret += carry(node.x, mID, quantity);
            mQuantity -= quantity;
        }
        if (mQuantity == 0)
            break;

        for (const auto& next : graph[node.x])
            if (!visited[next.x]) {
                visited[next.x] = true;
                lca = get_LCA(next.x, mID);
                dist = nodes[next.x].distance + nodes[mID].distance - 2 * nodes[lca].distance;
                Q.push({ next.x, dist });
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
