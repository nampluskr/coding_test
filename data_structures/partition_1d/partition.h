#pragma once

#include <cmath>

#define MAX_VALUES  1000
#define MAX_BUCKETS 100
#define INF 0x7fffffff

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

struct PartitionSum {
    struct Bucket {
        int sum;
    };
    Bucket buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;              // bucket size
    int num_buckets;    // num. of buckets

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { buckets[i] = {}; }
    }
    void update(int idx, int value) {
        buckets[idx / N].sum -= values[idx];
        values[idx] += value;
        buckets[idx / N].sum += value;
    }
    int query(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = min(right / N, num_buckets - 1);

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

struct PartionMinMax {
    struct Pair {
        int value, idx;
    };
    struct Bucket {
        Pair top = { -INF, -1 };    // { max_value, max_index }
        Pair bot = { INF, -1 };     // { min_value, min_index }

        void update(int idx, int value) {
            if (value > top.value) { top = { value, idx }; }
            if (value < bot.value) { bot = { value, idx }; }
        }
    };
    Bucket buckets[MAX_BUCKETS];
    int values[MAX_VALUES];
    int N;              // bucket size
    int num_buckets;    // num. of buckets

    void init(int num_values) {
        N = sqrt(num_values);
        num_buckets = ceil((double)num_values / N);
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { buckets[i] = {}; }
    }
    void update(int idx, int value) {
        values[idx] += value;
        buckets[idx / N].update(idx, value);
    }

};
