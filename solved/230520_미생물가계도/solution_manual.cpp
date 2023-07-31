#if 1
// Manual 885 ms: Tree (LCA), Partition (Range update + Point query)
// Array
#include <unordered_map>
#include <string>
using namespace std;

#define NUM_NODES	12'001
#define NUM_VALUES	1'000'001

#define BUCKET_SIZE	1'000	// sqrt(NUM_VALUES);
#define NUM_BUCKETS	1'001	// ceil((double)NUM_VALUES / N)

struct Node {
	int parent;
	int depth;
	int firstDay;
	int lastDay;
};
unordered_map<string, int> nodeMap;
Node nodes[NUM_NODES];
int nodeCnt;

struct Partition {
	int buckets[NUM_BUCKETS];
	int values[NUM_VALUES];
	int N;		// bucket size;

	void init() {
		N = BUCKET_SIZE;
		for (int i = 0; i < NUM_BUCKETS; i++) { buckets[i] = 0; }
		for (int i = 0; i < NUM_VALUES; i++) { values[i] = 0; }
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

	for (int i = 0; i < NUM_NODES; i++) { nodes[i] = { 0, 0, 0, 0 }; }
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