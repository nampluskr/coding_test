// STL 1728 ms: Partion (Range update + total query)
#include <vector>
using namespace std;

struct Result {
	int top;	// 가장 높은 블록의 높이
	int count;	// 남아 있는 블록들의 개수를 1,000,000으로 나눈 나머지
};
struct Data {
	int top;
	int bottom;
	int base;
	long long count;
};
struct Partition {
	vector<Data> buckets;
	vector<int> values;
	int N;		// bucket size

	void init(int num_values) {
		N = sqrt(num_values);
		int num_buckets = ceil((double)num_values / N);
		buckets.clear();	buckets.resize(num_buckets);
		values.clear();		values.resize(num_values);
	}
	void update_block(int bIdx) {
		int left = bIdx * N;
		int right = min((bIdx + 1) * N - 1, (int)values.size() - 1);

		buckets[bIdx].top = 0;
		buckets[bIdx].bottom = INT32_MAX;

		for (int i = left; i <= right; i++) {
			buckets[bIdx].top = max(buckets[bIdx].top, values[i]);
			buckets[bIdx].bottom = min(buckets[bIdx].bottom, values[i]);
		}
	}
	void update(int left, int right, int value) {
		int s = left / N;
		int e = right / N;

		if (s == e) {
			for (int i = left; i <= right; i++) {
				values[i] += value;
				buckets[i / N].count += value;
			}
			update_block(s);
			return;
		}
		while (left / N == s) {
			values[left] += value;
			buckets[left / N].count += value;
			left += 1;
		}
		while (right / N == e) {
			values[right] += value;
			buckets[right / N].count += value;
			right -= 1;
		}
		update_block(s);
		update_block(e);
		for (int i = s + 1; i <= e - 1; i++) {
			buckets[i].count += value * N;
			buckets[i].base += value;
		}
	}
	Result query() {
		Result ret{ 0, 0 };	// top, count
		int top = 0;
		int bottom = INT32_MAX;
		long long count = 0;

		for (int i = 0; i < buckets.size(); i++) {
			top = max(top, buckets[i].top + buckets[i].base);
			bottom = min(bottom, buckets[i].bottom + buckets[i].base);
			count += buckets[i].count;
		}
		ret.top = top - bottom;
		ret.count = (count - (long long)values.size() * bottom) % 1'000'000;
		return ret;
	}
};
Partition part;

/////////////////////////////////////////////////////////////////////
void init(int C)
{
	part.init(C);
}

// 3,000
Result dropBlocks(int mCol, int mHeight, int mLength)
{
	Result ret{ 0, 0 };	// top, count

	part.update(mCol, mCol + mLength - 1, mHeight);
	ret = part.query();
	return ret;
}