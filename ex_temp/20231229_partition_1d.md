### [Point Update] 구간합 / 구간 최대 / 구간 최소 구하기

```cpp
// point update_point / range query_range
#include <cmath>

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

#define MAX_VALUES  100
#define MAX_BUCKETS 10
#define INF 0x7fffffff


struct BucketSum {
    int sum;
};

struct PartitionSum {
    BucketSum buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;  // bucket size
    int num_buckets;

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) {
            buckets[i].sum = 0;
        }
    }
    void update_point(int idx, int value) {
        values[idx] += value;
        buckets[idx / N].sum += value;
    }
    int query_range(int left, int right) {
        int ret = 0;
        int s = left / N;       // first bucket index
        int e = right / N;      // last bucket index

        if (s == e) {
            for (int i = left; i <= right; i++) { ret += values[i]; }
            return ret;
        }
        while (left / N == s) { ret += values[left++]; }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i].sum; }
        while (right / N == e) { ret += values[right--]; }
        return ret;
    }
};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
struct Pair {
    int idx, value;
};

struct BucketMinMax {
    Pair max, min;
    int sIdx, eIdx;

    void update(int idx, int value) {
        if (value > max.value) { max = { idx, value }; }
        if (value < min.value) { min = { idx, value }; }
    }
};

struct PartitionMinMax {
    BucketMinMax buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;  // bucket size
    int num_buckets;

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { 
            buckets[i].max = { -1, -INF };
            buckets[i].min = { -1, INF };
            buckets[i].sIdx = i * N;
            buckets[i].eIdx = min((i + 1) * N - 1, num_values - 1);
        }
    }
    void update_point(int idx, int value) {
        values[idx] += value;
        int bIdx = idx / N;
        if (idx != buckets[bIdx].max.idx && idx != buckets[bIdx].min.idx) {
            buckets[bIdx].update(idx, value);
        }
        else {
            buckets[bIdx].max = { -1, -INF };
            buckets[bIdx].min = { -1, INF };
            for (int i = buckets[bIdx].sIdx; i <= buckets[bIdx].eIdx; i++) {
                buckets[bIdx].update(i, values[i]);
            }
        }
    }
    BucketMinMax query_range(int left, int right) {
        BucketMinMax ret = { { -1, -INF }, { -1, INF } };
        int s = left / N;       // first bucket index
        int e = right / N;      // last bucket index

        if (s == e) {
            for (int i = left; i <= right; i++) { ret.update(i, values[i]); }
            return ret;
        }
        while (left / N == s) { ret.update(left, values[left]); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.update(buckets[i].max.idx, buckets[i].max.value);
            ret.update(buckets[i].min.idx, buckets[i].min.value);
        }
        while (right / N == e) { ret.update(right, values[right]); right--; }
        return ret;
    }
};
```

### [Range Update] 구간합 / 구간 최대 / 구간 최소 구하기

```cpp
// reange update / range query
#include <cmath>

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

#define MAX_VALUES  100
#define MAX_BUCKETS 10
#define INF 0x7fffffff

struct BucketSum {
    int base;
    int sum;
};

struct PartitionSum {
    BucketSum buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;  // bucket size
    int num_buckets;

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) {
            buckets[i].base = 0;
            buckets[i].sum = 0;
        }
    }
    void update_point(int idx, int value) {
        values[idx] += value;
        buckets[idx / N].sum += value;
    }
    void update_range(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { update_point(i, value); }
            return;
        }
        while (left / N == s) { update_point(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].base += value;
            buckets[i].sum += value * N;
        }
        while (right / N == e) { update_point(right--, value); }
    }
    int query_point(int idx) { 
        return values[idx] + buckets[idx / N].base;
    }
    int query_sum(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret += query_point(i); }
            return ret;
        }
        while (left / N == s) { ret += query_point(left++); }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i].sum; }
        while (right / N == e) { ret += query_point(right--); }
        return ret;
    }
};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
struct Pair {
    int idx, value;
};

struct BucketMinMax{
    int base;
    Pair min, max;
    int sIdx, eIdx;

    void update(int idx, int value) {
        if (value > max.value) { max = { idx, value }; }
        if (value < min.value) { min = { idx, value }; }
    }
};

struct PartitionMinMax {
    BucketMinMax buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;  // bucket size
    int num_buckets;

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) {
            buckets[i].base = 0;
            buckets[i].max = { -1, -INF };
            buckets[i].min = { -1, INF };
            buckets[i].sIdx = i * N;
            buckets[i].eIdx = min((i + 1) * N - 1, num_values - 1);
        }
    }
    void update_point(int idx, int value) {
        values[idx] += value;
        int bIdx = idx / N;
        if (idx != buckets[bIdx].max.idx && idx != buckets[bIdx].min.idx) {
            buckets[bIdx].update(idx, value);
        }
        else {
            buckets[bIdx].max = { -1, -INF };
            buckets[bIdx].min = { -1, INF };
            for (int i = buckets[bIdx].sIdx; i <= buckets[bIdx].eIdx; i++) {
                buckets[bIdx].update(i, query_point(i));
            }
        }
    }
    void update_range(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { update_point(i, value); }
            return;
        }
        while (left / N == s) { update_point(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].base += value;
            buckets[i].max.value += value;
            buckets[i].min.value += value;
        }
        while (right / N == e) { update_point(right--, value); }
    }
    int query_point(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    BucketMinMax query_range(int left, int right) {
        BucketMinMax ret;
        ret.min = { -1, INF };
        ret.max = { -1, -INF };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret.update(i, query_point(i)); }
            return ret;
        }
        while (left / N == s) { ret.update(left, query_point(left)); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.update(buckets[i].max.idx, buckets[i].max.value + buckets[i].base);
            ret.update(buckets[i].min.idx, buckets[i].min.value + buckets[i].base);
        }
        while (right / N == e) { ret.update(right, query_point(right)); right--; }
        return ret;
    }
};
```
