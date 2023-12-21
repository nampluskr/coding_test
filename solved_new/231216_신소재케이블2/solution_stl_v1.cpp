#if 0
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

int maxDist;
vector<int> history;
vector<int> bestPath;

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
		for (int next: nodes[cur])
			if (visited[next] < 0) {
				visited[next] = visited[cur] + distMap[cur][next];
				Q.push(next);
			}
	}
	return visited[end];
}

void show_history(const vector<int>& hist, int dist) {
	printf(">> dist = %2d: ", dist);
	int i;
	for (i = 0; i < hist.size() - 1; ++i)
		printf("[%d] - ", hist[i]);
	printf("[%d]\n", hist[i]);
}

void dfs(int cur, int dist = 0, int depth = 1) {
	if (depth > 1 && nodes[cur].size() == 1) {
		maxDist = max(maxDist, dist);
		bestPath = history;
		//copy(bestPath.begin(), bestPath.end(), history.begin());
		//show_history(history, maxDist);
		return;
	}
	for (int next: nodes[cur])
		if (!visited[next] && dist + distMap[cur][next] > maxDist) {
			history.push_back(devices[next]);
			visited[next] = 1;
			dfs(next, dist + distMap[cur][next], depth + 1);
			visited[next] = 0;
			history.pop_back();
		}
}

/////////////////////////////////////////////////////////////////////
void init(int mDevice)
{
	for (int i = 0; i < MAX_NODES; ++i) { nodes[i].clear(); }
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

int test(int mDevice)
{
	int start = get_nodeIndex(mDevice);
	for (int i = 0; i < nodeCnt; ++i) { visited[i] = 0; }
	visited[start] = 1;
	history.clear();
	bestPath.clear();
	history.push_back(devices[start]);
	printf("=====================================\n");

	// 시작점일 때 - 최대값 1개의 값
	if (nodes[start].size() == 1) {
		maxDist = 0;
		printf("[%d]에서 시작 (최대값 선택)\n", devices[start]);
		dfs(start);
		show_history(bestPath, maxDist);
	}
	// 경유점일 때 - 최대값 2개의 합
	else {
		printf("[%d]를 경유 (최대값 2개의 합)\n", devices[start]);
		for (int child : nodes[start]) {
			history.push_back(devices[child]);
			if (nodes[child].size() > 1) {
				maxDist = 0;
				dfs(child, distMap[start][child]);
				show_history(bestPath, maxDist);
			}
			else {
				show_history(history, distMap[start][child]);
			}
			history.pop_back();
		}
	}
	return -1;
}
#endif