// Manual 704 ms: Partition (Point update)
#if 1
#define NUM_VALUES	200'000	// init() + add()
#define BUCKET_SIZE	447		// sqrt(NUM_VALUES)
#define NUM_BUCKETS	448		// ceil((double)NUM_VALUES / BUCKET_SIZE)

#define INF	2147483647		// (INT32_MAX)
#define DELETED	1

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

int values[NUM_VALUES];
int states[NUM_VALUES];
int totalCnt;
int cnt;

struct Data {
	int top;
	int bottom;
	int count;
};

struct Partition {
	Data buckets[NUM_BUCKETS];
	int N;		// bucket size

	void init() {
		N = BUCKET_SIZE;
		for (int i = 0; i < NUM_BUCKETS; i++) {
			buckets[i] = { 0, INF, 0 };
		}
	}
	void update_bucket(int bIdx) {
		int left = bIdx * N;
		int right = min((bIdx + 1) * N - 1, totalCnt - 1);

		buckets[bIdx] = { 0, INF, 0 };
		for (int i = left; i <= right; i++) {
			if (states[i] != DELETED) {
				buckets[bIdx].top = max(buckets[bIdx].top, values[i]);
				buckets[bIdx].bottom = min(buckets[bIdx].bottom, values[i]);
				buckets[bIdx].count += 1;
			}
		}
	}
	// Point update (Push back)
	void update(int idx, int value) {
		values[idx] = value;
		buckets[idx / N].top = max(buckets[idx / N].top, value);
		buckets[idx / N].bottom = min(buckets[idx / N].bottom, value);
		buckets[idx / N].count += 1;
	}
	Data query(int left, int right) {
		Data ret{ 0, INF, 0 };
		int s = left / N;
		int e = right / N;

		if (s == e) {
			for (int i = left; i <= right; i++) {
				if (states[i] != DELETED) {
					ret.top = max(ret.top, values[i]);
					ret.bottom = min(ret.bottom, values[i]);
					ret.count += 1;
				}
			}
			return ret;
		}
		while (left / N == s) {
			if (states[left] != DELETED) {
				ret.top = max(ret.top, values[left]);
				ret.bottom = min(ret.bottom, values[left]);
				ret.count += 1;
			}
			left += 1;
		}
		while (right / N == e) {
			if (states[right] != DELETED) {
				ret.top = max(ret.top, values[right]);
				ret.bottom = min(ret.bottom, values[right]);
				ret.count += 1;
			}
			right -= 1;
		}
		for (int i = s + 1; i <= e - 1; i++) {
			ret.top = max(ret.top, buckets[i].top);
			ret.bottom = min(ret.bottom, buckets[i].bottom);
			ret.count += buckets[i].count;
		}
		return ret;
	}
};
Partition part;

///////////////////////////////////////////////////////////
int get_bucketIdx(int newIdx) {
	int sum_cnt = 0;
	for (int i = 0; i < NUM_BUCKETS; i++) {
		sum_cnt += part.buckets[i].count;
		if (sum_cnt >= newIdx + 1) { return i; }
	}
	return -1;
}

int get_valueIdx(int newIdx) {
	int bIdx = get_bucketIdx(newIdx);
	int left = bIdx * part.N;
	int right = min((bIdx + 1) * part.N - 1, totalCnt - 1);

	int idx = 0;
	for (int i = 0; i < bIdx; i++) {
		idx += part.buckets[i].count;
	}
	for (int i = left; i <= right; i++) {
		if (states[i] != DELETED) { idx += 1; }
		if (idx == newIdx + 1) { return i; }
	}
	return -1;
}

///////////////////////////////////////////////////////////
void init(int N, int mValue[])
{
	for (int i = 0; i < NUM_VALUES; i++) {
		values[i] = 0;
		states[i] = 0;
	}
	totalCnt = 0;
	cnt = 0;

	part.init();
	for (int i = 0; i < N; i++) { part.update(totalCnt + i, mValue[i]); }
	totalCnt += N;
	cnt += N;
}

// 2,000
void add(int M, int mValue[])
{
	for (int i = 0; i < M; i++) { part.update(totalCnt + i, mValue[i]); }
	totalCnt += M;
	cnt += M;
}

// 500
// mTo - mFrom <= 100
void erase(int mFrom, int mTo)
{
	int left = get_valueIdx(mFrom - 1);
	int right = get_valueIdx(mTo - 1);

	for (int i = left; i <= right; i++) {
		if (states[i] != DELETED) {
			states[i] = DELETED;
			//values[i] = -1;
		}
	}

	int s = left / part.N;
	int e = right / part.N;
	for (int i = s; i <= e; i++) {
		part.update_bucket(i);
	}
	cnt -= mTo - mFrom + 1;
}

// 30,000
int find(int K)
{
	int left = get_valueIdx(cnt - K);
	int right = get_valueIdx(cnt - 1);

	Data ret = part.query(left, right);
	return ret.top - ret.bottom;
}
#endif