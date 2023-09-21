### [구간합 / 구간최대 / 구간최소]

```cpp
#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

#define INF 1000000001

long long min(long long a, long long b) { return (a < b) ? a : b; }
long long max(long long a, long long b) { return (a > b) ? a : b; }

struct Value {
    long long value;
    int idx;
};

struct Data {
    Value top;
    Value bot;
    long long sum;

    void update(int idx, long long value) {
        sum += value;
        if (value > top.value) {
            top.value = value;
            top.idx = idx;
        }
        if (value < bot.value) {
            bot.value = value;
            bot.idx = idx;
        }
    }
};

int bucket_size;
int num_buckets;
int num_values;

struct Partition {
    vector<Data> buckets;
    vector<long long> values;
    int N;      // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);

        for (int i = 0; i < num_buckets; i++) {
            buckets[i].top = { 0, -1};
            buckets[i].bot = { INF, -1 };
        }

    }
    void update(int idx, long long value) {
        buckets[idx / N].sum -= values[idx];
        values[idx] = value;
        buckets[idx / N].sum += value;

        int bIdx = idx / N;
        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, num_values - 1);

        if (idx != buckets[bIdx].top.idx) {
            if (value > buckets[bIdx].top.value) {
                buckets[bIdx].top.value = value;
                buckets[bIdx].top.idx = idx;
            }
        }
        else {
            buckets[bIdx].top.value = 0;
            for (int i = left; i <= right; i++) {
                if (buckets[i].top.value > buckets[bIdx].top.value) {
                    buckets[bIdx].top.value = buckets[i].top.value;
                    buckets[bIdx].top.idx = buckets[i].top.idx;
                }
            }
        }

        if (idx != buckets[idx / N].bot.idx) {
            if (value < buckets[bIdx].bot.value) {
                buckets[bIdx].bot.value = value;
                buckets[bIdx].bot.idx = idx;
            }
        }
        else {
            buckets[bIdx].bot.value = INF;
            for (int i = left; i <= right; i++) {
                if (buckets[i].bot.value > buckets[bIdx].bot.value) {
                    buckets[bIdx].bot.value = buckets[i].bot.value;
                    buckets[bIdx].bot.idx = buckets[i].bot.idx;
                }
            }
        }
    }
    Data query(int left, int right) {
        Data ret = { {0, -1}, {INF, -1}, 0 };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { 
                ret.update(i, values[i]);
            }
            return ret;
        }
        while (left / N == s) {
            ret.update(left, values[left]);
            left++;
        }
        while (right / N == e) {
            ret.update(right, values[right]);
            right--;
        }
        for (int i = s + 1; i < e - 1; i++) {
            ret.sum += buckets[i].sum;
            if (buckets[i].top.value > ret.top.value) {
                ret.top.value = buckets[i].top.value;
                ret.top.idx = buckets[i].top.idx;
            }
            if (buckets[i].bot.value < ret.bot.value) {
                ret.bot.value = buckets[i].bot.value;
                ret.bot.idx = buckets[i].bot.idx;
            }
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

    num_values = n;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();

    long long x;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        part.update(i, x);
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        Data ret = part.query(a - 1, b - 1);
        printf("%d %d\n", ret.bot.value, ret.top.value);
    }

    return 0;
}
#endif
```

### [구간합 / 구간최대(인덱스) / 구간최소(인덱스)]

```cpp
#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

#define INF 1000000001

struct Value {
    long long value;
    int idx;
};

struct Data {
    Value top;
    Value bot;
    long long sum;

    void update_top(int idx, long long value) {
        if (value > top.value) {
            top.value = value;
            top.idx = idx;
        }
    }
    void update_bot(int idx, long long value) {
        if (value < bot.value) {
            bot.value = value;
            bot.idx = idx;
        }
    }
};

int bucket_size;
int num_buckets;
int num_values;

struct Partition {
    vector<Data> buckets;
    vector<long long> values;
    int N;      // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);

        for (int i = 0; i < num_buckets; i++) {
            buckets[i].top = { 0, -1 };
            buckets[i].bot = { INF, -1 };
            buckets[i].sum = 0;
        }
    }
    void update(int idx, long long value) {
        int bIdx = idx / N;
        buckets[bIdx].sum -= values[idx];
        values[idx] = value;
        buckets[bIdx].sum += value;

        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, num_values - 1);

        if (idx == buckets[bIdx].top.idx && value > buckets[bIdx].top.value) {
            buckets[bIdx].top.value = 0;
            for (int i = left; i <= right; i++) {
                buckets[bIdx].update_top(i, values[i]);
            }
        }
        else { buckets[bIdx].update_top(idx, value); }

        if (idx == buckets[bIdx].bot.idx && value < buckets[bIdx].bot.value) {
            buckets[bIdx].bot.value = INF;
            for (int i = left; i <= right; i++) {
                buckets[bIdx].update_bot(i, values[i]);
            }
        }
        else { buckets[bIdx].update_bot(idx, value); }
    }
    Data query(int left, int right) {
        Data ret = { {0, -1}, {INF, -1}, 0 };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                ret.update_top(i, values[i]);
                ret.update_bot(i, values[i]);
                ret.sum += values[i];
            }
            return ret;
        }

        while (left / N == s) {
            ret.update_top(left, values[left]);
            ret.update_bot(left, values[left]);
            ret.sum += values[left++];
        }
        while (right / N == e) {
            ret.update_top(right, values[right]);
            ret.update_bot(right, values[right]);
            ret.sum += values[right--];
        }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.update_top(buckets[i].top.idx, buckets[i].top.value);
            ret.update_bot(buckets[i].bot.idx, buckets[i].bot.value);
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

    num_values = n;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();

    long long x;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        part.update(i, x);
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        Data ret = part.query(a - 1, b - 1);
        printf("%d %d\n", ret.bot.value, ret.top.value);
    }

    return 0;
}
#endif
```
