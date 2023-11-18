#pragma once

#define MINMAX

#define MAX_VALUES  10000
#define MAX_BUCKETS 100

int num_values;
int bucket_size;    // sqrt(num_values)
int num_buckets;    // ceil((double)num_values / bucket_size)

#ifndef MINMAX
struct Bucket {
    int sum, base;
};

struct PartitionRange {
    int values[MAX_VALUES];
    Bucket buckets[MAX_BUCKETS];    // base, sum
    int N;                          // bucket_size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_values; i++) { values[i] = 0; }
        for (int i = 0; i < num_buckets; i++) { buckets[i] = { 0, 0 }; }
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                values[i] += value;
                buckets[i / N].sum += value;
            }
            return;
        }
        while (left / N == s) {
            values[left++] += value;
            buckets[s].sum += value;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].base += value;
            buckets[i].sum += value * N;
        }
        while (right / N == e) {
            values[right--] += value;
            buckets[e].sum += value;
        }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    int query(int left, int right) {
        int ret = 0;
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret += query(i); }
            return ret;
        }
        while (left / N == s) { ret += query(left++); }
        while (right / N == e) { ret += query(right--); }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i].sum; }
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
    int base;

    void update(int idx, int value) {
        if (value > top.value) { top = { value, idx }; }
        if (value < bot.value) { bot = { value, idx }; }
    }
};

struct PartitionRange {
    int values[MAX_VALUES];
    Bucket buckets[MAX_BUCKETS];    // top, bot, base
    int N;                          // bucket_size

    void init() {
        N = bucket_size;
        for (int i = 0; i < num_values; i++) { values[i] = {}; }
        for (int i = 0; i < num_buckets; i++) {
            buckets[i] = { { -INF, -1}, { INF, -1 }, 0 };
        }
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                values[i] += value;
                buckets[i / N].update(i, query(i));
            }
            return;
        }
        while (left / N == s) {
            values[left] += value;
            buckets[s].update(left, query(left));
            left++;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].base += value;
            buckets[i].top.value += value;
            buckets[i].bot.value += value;
        }
        while (right / N == e) {
            values[right] += value;
            buckets[e].update(right, query(right));
            right--;
        }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    Bucket query(int left, int right) {
        Bucket ret = { { -INF, -1 }, { INF, -1 }, 0 };  // top, bot, base
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { ret.update(i, query(i)); }
            return ret;
        }
        while (left / N == s) { ret.update(left, query(left)); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.update(buckets[i].top.idx, buckets[i].top.value);
            ret.update(buckets[i].bot.idx, buckets[i].bot.value);
        }
        while (right / N == e) { ret.update(right, query(right)); right--; }
        return ret;
    }
};
#endif