// STL 5254 ms
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAXL (11) 

struct Node {
	int parent;		// 부모 노드 번호
	int depth;		// 루트 노드부터의 거리
};

unordered_map<string, int> nodeMap;
vector<Node> nodes;
vector<vector<int>> graph;

////////////////////////////////////////////////////////////////
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

int bfs(int start, int distance) {
	queue<int> Q;
	vector<int> dist(nodes.size(), -1);
	int cnt = 0;

	dist[start] = 0;
	Q.push(start);
	while (!Q.empty()) {
		int node = Q.front(); Q.pop();

		if (dist[node] > distance) break;
		if (dist[node] == distance) cnt++;

		for (int next : graph[node])
			if (dist[next] == -1) {
				dist[next] = dist[node] + 1;
				Q.push(next);
			}
	}
	return cnt;
}

////////////////////////////////////////////////////////////////
void init(char mRootSpecies[MAXL])
{
	nodeMap.clear();
	nodes.clear();

	int nIdx = nodes.size();
	nodeMap[string(mRootSpecies)] = nIdx;
	nodes.push_back({ -1, 0 });

	graph.clear();
	graph.push_back({});
}

void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
	int nIdx = nodes.size();
	nodeMap[string(mSpecies)] = nIdx;
	nodes.push_back({});

	int pIdx = nodeMap[string(mParentSpecies)];
	nodes[nIdx].parent = pIdx;
	nodes[nIdx].depth = nodes[pIdx].depth + 1;

	graph.push_back({});
	graph[nIdx].push_back(pIdx);
	graph[pIdx].push_back(nIdx);
}

// LCA
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
	int x = nodeMap[string(mSpecies1)];
	int y = nodeMap[string(mSpecies2)];
	int lca = get_LCA(x, y);

	return nodes[x].depth + nodes[y].depth - 2 * nodes[lca].depth;
}

// BFS
int getCount(char mSpecies[MAXL], int mDistance)
{
	int start = nodeMap[string(mSpecies)];
	return bfs(start, mDistance);
}
