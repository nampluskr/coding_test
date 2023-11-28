#include <vector>
#include <queue>
using namespace std;

#define MAX_NODES   10
#define INF 0xfffffff

struct Data {
    int idx;
    int dist;
    bool operator<(const Data& data) const { return dist > data.dist; }
};

struct Node {
    vector<Data> nodeList;
};
Node nodes[MAX_NODES];
int nodeCnt;
int dist[MAX_NODES];


void init() {
    nodeCnt = 7;

    nodes[1].nodeList.push_back({ 2, 2 });
    nodes[1].nodeList.push_back({ 4, 1 });
    nodes[1].nodeList.push_back({ 3, 5 });

    nodes[2].nodeList.push_back({ 3, 3 });
    nodes[2].nodeList.push_back({ 4, 2 });

    nodes[3].nodeList.push_back({ 2, 3 });
    nodes[3].nodeList.push_back({ 6, 5 });

    nodes[4].nodeList.push_back({ 3, 3 });
    nodes[4].nodeList.push_back({ 5, 1 });

    nodes[5].nodeList.push_back({ 3, 1 });
    nodes[5].nodeList.push_back({ 6, 2 });
}

void dijkstra(int start) {
    priority_queue<Data> Q;
    for (int i = 0; i < nodeCnt; i++) { dist[i] = INF; }

    dist[start] = 0;
    Q.push({ start, 0 });
    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();

        if (dist[cur.idx] < cur.dist) continue;

        for (auto next : nodes[cur.idx].nodeList) {
            if (dist[next.idx] > dist[cur.idx] + next.dist) {
                dist[next.idx] = dist[cur.idx] + next.dist;
                Q.push({ next.idx, dist[next.idx] });
            }
        }
    }
}


int main()
{
    init();
    dijkstra(1);

    // 0 2 3 1 2 4
    for (int i = 1; i < nodeCnt; i++) { printf("%d ", dist[i]); }
    printf("\n");

    return 0;
}