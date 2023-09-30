#if 1
// Manual 920 ms: Partion (Range update + total query)
#include <cmath>

#define MAX_VALUES      1000000
#define MAX_BUCKETS     1000
#define INF             10000

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

struct Result {
    int top;
    int count;
};

int num_values;
int num_buckets;
int bucket_size;

struct Data {
    int top;
    int bot;
    long long sum;
    int base;
};

struct Partition {
    Data buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;                // bucket size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { buckets[i] = {}; }
    }
    void update_minmax(int bIdx) {
        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, num_values - 1);

        buckets[bIdx].top = 0;
        buckets[bIdx].bot = INF;
        for (int i = left; i <= right; i++) {
            buckets[bIdx].top = max(buckets[bIdx].top, query(i));
            buckets[bIdx].bot = min(buckets[bIdx].bot, query(i));
        }
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                values[i] += value;
                buckets[s].sum += value;
            }
            update_minmax(s);
            return;
        }
        while (left / N == s) {
            values[left++] += value;
            buckets[s].sum += value;
        }
        update_minmax(s);
        while (right / N == e) {
            values[right--] += value;
            buckets[e].sum += value;
        }
        update_minmax(e);
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].top += value;
            buckets[i].bot += value;
            buckets[i].sum += value * N;
            buckets[i].base += value;
        }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    Data query() {
        Data data = { 0, INF, 0 };

        for (int i = 0; i < num_buckets; i++) {
            if (buckets[i].sum > 0) {
                data.top = max(data.top, buckets[i].top);
                data.bot = min(data.bot, buckets[i].bot);
                data.sum += buckets[i].sum;
            }
        }
        return data;
    }
};
Partition part;

/////////////////////////////////////////////////////////////////////
void init(int C)
{
    bucket_size = sqrt(C);
    num_values = C;
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();
}

// 3,000
Result dropBlocks(int mCol, int mHeight, int mLength)
{
    Result ret{ 0, 0 };    // top, sum

    part.update(mCol, mCol + mLength - 1, mHeight);
    Data data = part.query();

    ret.top = data.top - data.bot;
    ret.count = (data.sum - (long long)num_values * data.bot) % 1000000;
    return ret;
}
#endif