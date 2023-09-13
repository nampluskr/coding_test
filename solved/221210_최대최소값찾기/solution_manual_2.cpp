// STL 2065 ms
#if 0

#define MAX_VALUES	200000		// init() + add()
#define INF			2147483647
#define DELETED		1

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

const int num_values = MAX_VALUES;
const int bucket_size = 447;		// sqrt(MAX_VALUES);
const int num_buckets = 448;		// ceil((double)num_values / bucket_size);

int totalCnt;
int cnt;

struct Data {
	int top;
	int bot;
	int cnt;

	void update(int value) {
		top = max(top, value);
		bot = min(bot, value);
		cnt += 1;
	}
};

struct Partition {
	Data buckets[num_buckets];
	int values[num_values];
	int states[num_values];
	int N;		// bucket size

	void init() {
		N = bucket_size;
		for (int i = 0; i < num_buckets; i++) { buckets[i] = { 0, INF, 0}; }
		for (int i = 0; i < num_values; i++) { values[i] = 0; }
		for (int i = 0; i < num_values; i++) { states[i] = 0; }
	}
	void update_bucket(int bIdx) {
		int left = bIdx * N;
		int right = min((bIdx + 1) * N - 1, totalCnt - 1);

		buckets[bIdx] = {0, INF, 0};
		for (int i = left; i <= right; i++) {
			if (states[i] != DELETED) {
				buckets[bIdx].top = max(buckets[bIdx].top, values[i]);
				buckets[bIdx].bot = min(buckets[bIdx].bot, values[i]);
				buckets[bIdx].cnt += 1;
			}
		}
	}
	void add(int idx, int value) {
		values[idx] += value;

		buckets[idx / N].top = max(buckets[idx / N].top, value);
		buckets[idx / N].bot = min(buckets[idx / N].bot, value);
		buckets[idx / N].cnt += 1;
	}
	Data query(int left, int right) {
		Data ret{ 0, INF, 0 };
		int s = left / N;
		int e = right / N;

		if (s == e) {
			for (int i = left; i <= right; i++) {
				if (states[i] != DELETED) { ret.update(values[i]); }
			}
			return ret;
		}
		while (left / N == s) {
			if (states[left] != DELETED) { ret.update(values[left]); }
			left += 1;
		}
		while (right / N == e) {
			if (states[right] != DELETED) { ret.update(values[right]); }
			right -= 1;
		}
		for (int i = s + 1; i <= e - 1; i++) {
			ret.top = max(ret.top, buckets[i].top);
			ret.bot = min(ret.bot, buckets[i].bot);
			ret.cnt += buckets[i].cnt;
		}
		return ret;
	}
	int get_bucketIndex(int newIdx);
	int get_valueIndex(int newIdx);
};
Partition part;

///////////////////////////////////////////////////////////
int Partition::get_bucketIndex(int newIdx) {
	int sum_cnt = 0;
	for (int i = 0; i < num_buckets; i++) {
		sum_cnt += buckets[i].cnt;
		if (sum_cnt >= newIdx + 1) { return i; }
	}
	return -1;
}

int Partition::get_valueIndex(int newIdx) {
	int bIdx = get_bucketIndex(newIdx);
	int left = bIdx * N;
	int right = min((bIdx + 1) * N - 1, totalCnt - 1);

	int idx = 0;
	for (int i = 0; i < bIdx; i++) {
		idx += buckets[i].cnt;
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
	totalCnt = 0;
	cnt = 0;

	part.init();
	for (int i = 0; i < N; i++) { 
		part.add(totalCnt + i, mValue[i]);
	}
	totalCnt += N;
	cnt += N;
}

// 2,000
void add(int M, int mValue[])
{
	for (int i = 0; i < M; i++) {
		part.add(totalCnt + i, mValue[i]);
	}
	totalCnt += M;
	cnt += M;
}

// 500
void erase(int mFrom, int mTo)
{
	int left = part.get_valueIndex(mFrom - 1);
	int right = part.get_valueIndex(mTo - 1);

	for (int i = left; i <= right; i++) {
		if (part.states[i] != DELETED) {
			part.states[i] = DELETED;
		}
		part.update_bucket(i / part.N);
	}
	cnt -= mTo - mFrom + 1;
}

// 30,000
int find(int K)
{
	int left = part.get_valueIndex(cnt - K);
	int right = part.get_valueIndex(cnt - 1);

	Data ret = part.query(left, right);
	return ret.top - ret.bot;
}
#endif
