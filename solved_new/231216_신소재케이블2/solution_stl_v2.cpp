#if 1
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_NODES	10000

vector<int> nodes[MAX_NODES];
int nodeCnt;
unordered_map<int, int> nodeMap;

int devices[MAX_NODES];
int distMap[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
queue<int> Q;
priority_queue<int> PQ;

int maxDist;

/////////////////////////////////////////////////////////////////////
int get_nodeIndex(int mDevice) {
	int nIdx;
	auto iter = nodeMap.find(mDevice);
	if (iter == nodeMap.end()) {
		nIdx = nodeCnt++;
		nodeMap.emplace(mDevice, nIdx);
	}
	else { nIdx = iter->second; }
	return nIdx;
}

int bfs(int start, int end) {
	for (int i = 0; i < nodeCnt; ++i) { visited[i] = -1; }
	while (!Q.empty()) { Q.pop(); }
	visited[start] = 0;
	Q.push(start);

	while (!Q.empty()) {
		int cur = Q.front(); Q.pop();

		if (cur == end) { break; }
		for (int next : nodes[cur])
			if (visited[next] < 0) {
				visited[next] = visited[cur] + distMap[cur][next];
				Q.push(next);
			}
	}
	return visited[end];
}

void dfs(int cur, int dist = 0, int depth = 1) {
	if (depth > 1 && nodes[cur].size() == 1) {
	//if (depth > 1) {
		maxDist = dist;
		//maxDist = max(maxDist, dist);
		return;
	}
	for (int next : nodes[cur])
		if (!visited[next] && dist + distMap[cur][next] > maxDist) {
			visited[next] = 1;
			dfs(next, dist + distMap[cur][next], depth + 1);
			visited[next] = 0;
		}
}

/////////////////////////////////////////////////////////////////////
void init(int mDevice)
{
	for (int i = 0; i < MAX_NODES; ++i) {
		nodes[i].clear();
		//for (int j = 0; j < MAX_NODES; ++j)
		//	distMap[i][j] = 0;
	}
	nodeCnt = 0;
	nodeMap.clear();
}

void connect(int mOldDevice, int mNewDevice, int mLatency)
{
	int oldIdx = get_nodeIndex(mOldDevice);
	int newIdx = get_nodeIndex(mNewDevice);

	nodes[oldIdx].push_back(newIdx);
	nodes[newIdx].push_back(oldIdx);

	distMap[oldIdx][newIdx] = mLatency;
	distMap[newIdx][oldIdx] = mLatency;

	// for debugging
	devices[oldIdx] = mOldDevice;
	devices[newIdx] = mNewDevice;
}

int measure(int mDevice1, int mDevice2)
{
	int start = get_nodeIndex(mDevice1);
	int end = get_nodeIndex(mDevice2);
	int ret = bfs(start, end);
	return ret;
}

int get_sumTop2() {
	int ret = 0, cnt = 0;
	while (!PQ.empty() && cnt < 2) { ret += PQ.top(); PQ.pop(); cnt++; }
	return ret;
}

int test(int mDevice)
{
	int start = get_nodeIndex(mDevice);
	int ret = 0;

	// 시작점일 때 - 최대값 1개의 값
	if (nodes[start].size() == 1) {
		for (int i = 0; i < nodeCnt; ++i) { visited[i] = 0; }
		visited[start] = 1;
		maxDist = 0;
		dfs(start);
		ret = maxDist;
	}
	// 경유점일 때 - 최대값 2개의 합
	else {
		while (!PQ.empty()) { PQ.pop(); }

		for (int child : nodes[start]) {
			if (nodes[child].size() > 1) {
				for (int i = 0; i < nodeCnt; ++i) { visited[i] = 0; }
				visited[start] = 1;
				visited[child] = 1;
				maxDist = 0;
				dfs(child, distMap[start][child]);
				PQ.push(maxDist);
			}
			else {
				PQ.push(distMap[start][child]);
			}
		}
		ret = get_sumTop2();
	}
	return ret;
}
#endif