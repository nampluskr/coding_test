#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

#define INF 1000000001

long long min(long long a, long long b) { return (a < b) ? a : b; }
long long max(long long a, long long b) { return (a > b) ? a : b; }

struct Data {
    long long top;
    long long bot;
    long long sum;

    void update(long long value) {
        top = max(top, value);
        bot = min(bot, value);
        sum += value;
    }
};

struct Partition {
    vector<Data> buckets;
    vector<long long> values;
    int N;      // bucket size

    void init(int num_values) {
        N = sqrt(num_values);
        int num_buckets = ceil((double)num_values / N);
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update_minmax(int bIdx) {
        int left = bIdx * N;
        int right = min((bIdx + 1)*N - 1, values.size() - 1);

        buckets[bIdx].top = 0;
        buckets[bIdx].bot = INF;
        for (int i = left; i <= right; i++) {
            buckets[bIdx].top = max(buckets[bIdx].top, values[i]);
            buckets[bIdx].bot = min(buckets[bIdx].bot, values[i]);
        }
    }
    void update(int idx, long long value) {
        buckets[idx / N].sum -= values[idx];
        values[idx] += value;
        buckets[idx / N].sum += value;
        update_minmax(idx / N);
    }
    Data query(int left, int right) {
        Data ret = { 0, INF, 0 };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {  ret.update(values[i]); }
            return ret;
        }

        while (left / N == s) { ret.update(values[left++]); }
        while (right / N == e) { ret.update(values[right--]); }
        for (int i = s + 1; i <= e - 1; i++) { 
            ret.top = max(ret.top, buckets[i].top);
            ret.bot = min(ret.bot, buckets[i].bot);
            ret.sum += buckets[i].sum;
        }
        return ret;
    }
};
Partition part;

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int x;
    part.init(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        part.update(i, x);
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        Data ret = part.query(a - 1, b - 1);
        printf("%d %d\n", ret.bot, ret.top);
    }

    return 0;
}