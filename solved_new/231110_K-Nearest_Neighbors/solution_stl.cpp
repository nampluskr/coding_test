#if 1
// STL 1309 ms
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_SAMPLES 20000	// addSample() 함수의 호출 횟수 20,000 이하
#define MAX_TYPES	11		// 자료의 범주 (1 ≤ mC ≤ 10)
#define MAX_SIZE	4001	// 자료의 x축, y축 위치 (1 ≤ mX, mY ≤ 4,000)

#define ADDED	0
#define REMOVED	1

#define N	100				// 개별 파티션 크기
#define MAX_BUCKETS	200		// 파티션 전체 개수

struct Sample {
	int mX, mY, mC, state;
	int dist(int mX, int mY) { return abs(this->mX - mX) + abs(this->mY - mY); }
};

struct Data {
	int dist, mX, mY, sIdx;
	bool operator<(const Data& data) const {
		return (dist > data.dist) || (dist == data.dist && mX > data.mX) ||
			   (dist == data.dist && mX == data.mX && mY > data.mY);
	}
};

Sample samples[MAX_SAMPLES];
int sampleCnt;
unordered_map<int, int> sampleMap;
vector<int> sampleList[MAX_BUCKETS][MAX_BUCKETS];

int K;		// 근접 이웃 개수
int L;		// 아웃라이어 범위

int get_sampleIndex(int mID) {
	int sIdx;
	auto ptr = sampleMap.find(mID);
	if (ptr == sampleMap.end()) {
		sIdx = sampleCnt++;
		sampleMap.emplace(mID, sIdx);
	}
	else { sIdx = ptr->second; }
	return sIdx;
}

////////////////////////////////////////////////////////////////////
void init(int _K, int _L)
{
	K = _K;
	L = _L;
	for (int i = 0; i < MAX_SAMPLES; i++) { samples[i] = {}; }
	sampleCnt = 0;
	sampleMap.clear();

	for (int i = 0; i < MAX_BUCKETS; i++)
		for (int j = 0; j < MAX_BUCKETS; j++)
			sampleList[i][j].clear();
}

void addSample(int mID, int mX, int mY, int mC)
{
	int sIdx = get_sampleIndex(mID);
	samples[sIdx] = { mX, mY, mC, ADDED };					// 전체 탐색
	sampleList[(mX - 1) / N][(mY - 1) / N].push_back(sIdx);	// 부분 탐색
}

void deleteSample(int mID)
{
	int sIdx = get_sampleIndex(mID);
	samples[sIdx].state = REMOVED;
}

int predict(int mX, int mY)
{
	priority_queue<Data> Q;

	// 전체 탐색 + 힙정렬
	//for (int sIdx = 0; sIdx < sampleCnt; sIdx++) {
	//	if (samples[sIdx].state == REMOVED) continue;
	//	Q.push({ samples[sIdx].dist(mX, mY), samples[sIdx].mX, samples[xIdx].mY, sIdx });
	//}

	// 부분 탐색 + 힙정렬
	int spX = max((mX - 1 - L) / N, 0);
	int spY = max((mY - 1 - L) / N, 0);
	int epX = min((mX - 1 + L) / N, MAX_BUCKETS - 1);
	int epY = min((mY - 1 + L) / N, MAX_BUCKETS - 1);

	for (int i = spX; i <= epX; i++)
		for (int j = spY; j <= epY; j++)
			for (int sIdx: sampleList[i][j]) {
				if (samples[sIdx].state == REMOVED) continue;
				Q.push({ samples[sIdx].dist(mX, mY), samples[sIdx].mX, samples[sIdx].mY, sIdx });
			}

	// KNN 선택
	int cnt = 0;
	int topk[MAX_TYPES] = {};
	while (!Q.empty() && cnt < K) {
		auto data = Q.top(); Q.pop();
		if (data.dist > L) { return -1; }
		topk[samples[data.sIdx].mC] += 1;
		cnt += 1;
	}

	// 범주 판정
	int ret = 1;
	for (int mC = 2; mC < MAX_TYPES; mC++) {
		if (topk[mC] > topk[ret]) { ret = mC; }
		else if (topk[mC] == topk[ret] && mC < ret) { ret = mC; }
	}
	return ret;
}
#endif