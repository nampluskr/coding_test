#pragma once

#define MINMAX

#define MAX_VALUES  10000
#define MAX_BUCKETS 100

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

int num_values;
int bucket_size;    // sqrt(num_values)
int num_buckets;    // ceil((double)num_values / bucket_size)

#ifndef MINMAX
struct Bucket {
    int sum;
};

struct PartitionPoint {
    int values[MAX_VALUES];
    Bucket buckets[MAX_BUCKETS];
    int N;      // bucket_size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { buckets[i] = { 0 }; }
    }
    void update(int idx, int value) {
        buckets[idx / N].sum -= values[idx];
        values[idx] += value;
        buckets[idx / N].sum += value;
    }
    int query(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = right / N;

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

#else
#define INF 0xffffff

struct Bucket {
    struct Data {
        int value, idx;
    };
    Data top, bot;

    void update(int idx, int value) {
        if (value > top.value) { top = { value, idx }; }
        if (value < bot.value) { bot = { value, idx }; }
    }
};

struct PartitionPoint {
    int values[MAX_VALUES];
    Bucket buckets[MAX_BUCKETS];
    int N;      // bucket size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_values; i++) { values[i] = {}; }
        for (int i = 0; i < num_buckets; i++) {
            buckets[i] = { { -INF, -1 }, { INF, -1 } };
        }
    }
    void update(int idx, int value) {
        values[idx] += value;
        int bIdx = idx / N;

        if (idx == buckets[bIdx].top.idx || idx == buckets[bIdx].bot.idx) {
            buckets[bIdx] = { {-INF, -1}, {INF, -1} };
            int left = bIdx * N;
            int right = min((bIdx + 1) * N - 1, num_buckets - 1);
            for (int i = left; i <= right; i++) {
                buckets[bIdx].update(i, values[i]);
            }
        }
        else { buckets[bIdx].update(idx, value); }
    }
    Bucket query(int left, int right) {
        Bucket ret = { {-INF, -1}, { INF, -1 } };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret.update(i, values[i]); }
            return ret;
        }
        while (left / N == s) { ret.update(left, values[left]); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.update(buckets[i].top.idx, buckets[i].top.value);
            ret.update(buckets[i].bot.idx, buckets[i].bot.value);
        }
        while (right / N == e) { ret.update(right, values[right]); right--; }
        return ret;
    }
};
#endif