#if 0
// STL 7191 ms (WS)
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#define MAXL		(11) 
#define NUM_NODES	(50000)

struct Node {
	//char name[MAXL];
	int parent;
	int depth;
	vector<int> childList;
};
unordered_map<string, int> nodeMap;
vector<Node> nodes;
int nodeCnt;

////////////////////////////////////////////////////////////////
int get_nodeIndex(char mSpecies[]) {
	int nIdx;
	auto ptr = nodeMap.find(string(mSpecies));
	if (ptr == nodeMap.end()) {
		nIdx = nodeCnt;
		nodeMap[string(mSpecies)] = nIdx;
		nodeCnt += 1;
	}
	else { nIdx = ptr->second; }
	return nIdx;
}

int get_LCA(int x, int y) {
	if (nodes[x].depth < nodes[y].depth) {
		swap(x, y);
	}
	while(nodes[x].depth != nodes[y].depth) {
		x = nodes[x].parent;
	}
	while (x != y) {
		x = nodes[x].parent;
		y = nodes[y].parent;
	}
	return x;
}

////////////////////////////////////////////////////////////////
void init(char mRootSpecies[MAXL])
{
	nodeMap.clear();
	nodes.clear();	nodes.resize(NUM_NODES);
	nodeCnt = 0;

	int nIdx = get_nodeIndex(mRootSpecies);
	//strcpy(nodes[nIdx].name, mRootSpecies);
	nodes[nIdx].parent = -1;
}

// 50,000
void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
	int nIdx = get_nodeIndex(mSpecies);
	int pIdx = get_nodeIndex(mParentSpecies);

	//strcpy(nodes[nIdx].name, mSpecies);
	nodes[nIdx].parent = pIdx;
	nodes[nIdx].depth = nodes[pIdx].depth + 1;

	// 그래프 인접 리스트
	nodes[nIdx].childList.push_back(pIdx);
	nodes[pIdx].childList.push_back(nIdx);
}

// 10,000 LCA
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
	int x = get_nodeIndex(mSpecies1);
	int y = get_nodeIndex(mSpecies2);
	int lca = get_LCA(x, y);

	int ret = nodes[x].depth + nodes[y].depth - nodes[lca].depth * 2;
	return ret;
}

// 10,000 BFS
int getCount(char mSpecies[MAXL], int mDistance)
{
	int start = get_nodeIndex(mSpecies);
	queue<int> Q;
	vector<int> dist(nodeCnt, -1);
	int ret = 0;

	dist[start] = 0;
	Q.push(start);
	while (!Q.empty()) {
		int node = Q.front(); Q.pop();

		if (dist[node] > mDistance) { break; }
		if (dist[node] == mDistance) { ret += 1; }

		for (int next: nodes[node].childList)
			if (dist[next] == -1) {
				dist[next] = dist[node] + 1;
				Q.push(next);
			}
	}
	return ret;
}
#endif
