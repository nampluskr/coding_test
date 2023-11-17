#if 0
// Manual 943 ms
#define MAX_SAMPLES 20000	// addSample() 함수의 호출 횟수 20,000 이하
#define MAX_TYPES	11		// 자료의 범주 (1 ≤ mC ≤ 10)
#define MAX_SIZE	4001	// 자료의 x축, y축 위치 (1 ≤ mX, mY ≤ 4,000)

#define ADDED	0
#define REMOVED	1

#define N	100				// 개별 파티션 크기
#define MAX_BUCKETS	200		// 파티션 전체 개수


inline int abs(int x) { return (x > 0) ? x : -x; }
inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

template<typename Type>
struct LinkedList {
	struct ListNode {
		Type data;
		ListNode* next;
	};
	ListNode* head;
	ListNode* tail;

	void clear() { head = nullptr; tail = nullptr; }
	void push_back(const Type& data) {
		ListNode* node = new ListNode({ data, nullptr });
		if (head == nullptr) { head = node; tail = node; }
		else { tail->next = node; tail = node; }
	}
};

#define MAX_TABLE	10007
struct IntHashMapInt {
	struct Pair {
		int key, value;
	};
	LinkedList<Pair> table[MAX_TABLE];

	void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
	int find(int key) {
		int hash = key % MAX_TABLE;
		for (auto ptr = table[hash].head; ptr; ptr = ptr->next) {
			if (ptr->data.key == key)
				return ptr->data.value;
		}
		return -1;
	}
	void emplace(int key, int value) {
		int hash = key % MAX_TABLE;
		table[hash].push_back({ key, value });
	}
};

////////////////////////////////////////////////////////////////////
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
IntHashMapInt sampleMap;
LinkedList<int> sampleList[MAX_BUCKETS][MAX_BUCKETS];

int K;		// 근접 이웃 개수
int L;		// 아웃라이어 범위

template<typename Type>
struct PriorityQueue {
	Type heap[MAX_SAMPLES];
	int heapSize;

	void clear() { heapSize = 0; }
	void push(const Type& data) {
		heap[heapSize] = data;
		int current = heapSize;

		while (current > 0 && heap[(current - 1) / 2] < heap[current]) {
			Type temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}
		heapSize = heapSize + 1;
	}
	void pop() { 
		heapSize = heapSize - 1;
		heap[0] = heap[heapSize];
		int current = 0;

		while (current * 2 + 1 < heapSize) {
			int child;
			if (current * 2 + 2 == heapSize) {
				child = current * 2 + 1;
			}
			else {
				child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
			}
			if (heap[child] < heap[current]) {
				break;
			}
			Type temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;
			current = child;
		}
	}
	Type top() { return heap[0]; }
	bool empty() { return heapSize == 0; }
};

int get_sampleIndex(int mID) {
	int sIdx;
	auto ret = sampleMap.find(mID);
	if (ret == -1) {
		sIdx = sampleCnt++;
		sampleMap.emplace(mID, sIdx);
	}
	else { sIdx = ret; }
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
	PriorityQueue<Data> Q;	Q.clear();

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
			for (auto ptr = sampleList[i][j].head; ptr; ptr = ptr->next) {
				int sIdx = ptr->data;
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