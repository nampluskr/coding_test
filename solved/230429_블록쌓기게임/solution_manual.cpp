#if 0
// Manual 871 ms: Partion (Range update + total query)
// Array
#define NUM_VALUES    1'000'000
#define BUCKET_SIZE    1'000        // sqrt(NUM_VALUES)
#define NUM_BUCKETS    1'000        // ceil((double)NUM_VALUES / BUCKET_SIZE)
#define INT32_MAX    2147483647    // INT32_MAX

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

struct Result {
    int top;    // 가장 높은 블록의 높이
    int count;    // 남아 있는 블록들의 개수를 1,000,000으로 나눈 나머지
};

struct Data {
    int top;
    int bottom;
    int base;
    long long count;
};

struct Partition {
    Data buckets[NUM_BUCKETS];
    int values[NUM_VALUES];
    int N;                // bucket size
    int columnCnt;        // number of columns

    void init(int num_columns) {
        N = BUCKET_SIZE;
        columnCnt = num_columns;
        for (int i = 0; i < columnCnt; i++) { values[i] = 0; }
        for (int i = 0; i < NUM_BUCKETS; i++) { buckets[i] = { 0, 0, 0, 0 }; }
    }
    void update_block(int bIdx) {
        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, columnCnt - 1);

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
        Result ret{ 0, 0 };    // top, count
        int top = 0;
        int bottom = INT32_MAX;
        long long count = 0;

        for (int i = 0; i < NUM_BUCKETS; i++) {
            if (buckets[i].count > 0) {
                top = max(top, buckets[i].top + buckets[i].base);
                bottom = min(bottom, buckets[i].bottom + buckets[i].base);
                count += buckets[i].count;
            }
        }
        ret.top = top - bottom;
        ret.count = (count - (long long)columnCnt * bottom) % 1'000'000;
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
    Result ret{ 0, 0 };    // top, count

    part.update(mCol, mCol + mLength - 1, mHeight);
    ret = part.query();
    return ret;
}
#endif