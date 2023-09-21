### [구간합]

```cpp
// BOJ Pass 10999
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

int bucket_size;
int num_buckets;
int num_values;

struct Bucket {
    long long base;
    long long sum;
};

struct Partition {
    vector<Bucket> buckets;
    vector<long long> values;
    int N;                        // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update(int left, int right, long long value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { 
                values[i] += value;
                buckets[s].sum += value;
            }
            return;
        }
        while (left / N == s) { 
            values[left++] += value;
            buckets[s].sum += value;
        }
        while (right / N == e) { 
            values[right--] += value;
            buckets[e].sum += value;
        }
        for (int i = s + 1; i <= e - 1; i++) { 
            buckets[i].base += value;
            buckets[i].sum += value * N;
        }
    }
    long long query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    long long query(int left, int right) {
        long long ret = 0;
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
Partition part;

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    num_values = n;
    bucket_size = sqrt(n);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();

    long long x;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        part.update(i, i, x);
    }

    int cmd, left, right;
    long long value;

    for (int i = 0; i < m + k; i++) {
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d %d %lld", &left, &right, &value);
            part.update(left - 1, right - 1, value);
        }
        if (cmd == 2) {
            scanf("%d %d", &left, &right);
            printf("%lld\n", part.query(left - 1, right - 1));
        }
    }

    return 0;
}
```

### [구간합 / 구간최대 / 구간최소]

```cpp
// BOJ Pass 10999 Time Over
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cmath>
#include <vector>
#include <cstdint>
using namespace std;

#define INF INT64_MAX

int bucket_size;
int num_buckets;
int num_values;

struct Pair {
    long long value;
    int idx;
};

struct Bucket {
    long long base;
    long long sum;
    Pair top;
    Pair bot;

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

struct Partition {
    vector<Bucket> buckets;
    vector<long long> values;
    int N;                        // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update_bucket(int bIdx) {
        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, num_values - 1);

        buckets[bIdx].top.value = -INF;
        buckets[bIdx].bot.value = INF;
        for (int i = left; i <= right; i++) {
            buckets[bIdx].update_top(i, query(i));
            buckets[bIdx].update_bot(i, query(i));
        }
    }
    void update(int left, int right, long long value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                values[i] += value;
                buckets[s].sum += value;
            }
            update_bucket(s);
            return;
        }
        while (left / N == s) {
            values[left++] += value;
            buckets[s].sum += value;
        }
        update_bucket(s);
        while (right / N == e) {
            values[right--] += value;
            buckets[e].sum += value;
        }
        update_bucket(e);
        for (int i = s + 1; i <= e - 1; i++) {
            buckets[i].base += value;
            buckets[i].top.value += value;
            buckets[i].bot.value += value;
            buckets[i].sum += value * N;
        }
    }
    long long query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    Bucket query(int left, int right) {
        Bucket ret = { 0, 0, {-INF, -1}, {INF, -1} };
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { 
                ret.sum += query(i);
                ret.update_top(i, query(i));
                ret.update_bot(i, query(i));
            }
            return ret;
        }
        while (left / N == s) { 
            ret.sum += query(left);
            ret.update_top(left, query(left));
            ret.update_bot(left, query(left));
            left++;
        }
        while (right / N == e) { 
            ret.sum += query(right);
            ret.update_top(right, query(right));
            ret.update_bot(right, query(right));
            right--;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            ret.sum += buckets[i].sum;
            ret.update_top(buckets[i].top.idx, buckets[i].top.value);
            ret.update_bot(buckets[i].bot.idx, buckets[i].bot.value);
        }
        return ret;
    }
};
Partition part;

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    num_values = n;
    bucket_size = sqrt(n);
    num_buckets = ceil((double)num_values / bucket_size);
    part.init();

    long long x;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        part.update(i, i, x);
    }

    int cmd, left, right;
    long long value;

    for (int i = 0; i < m + k; i++) {
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d %d %lld", &left, &right, &value);
            part.update(left - 1, right - 1, value);
        }
        if (cmd == 2) {
            scanf("%d %d", &left, &right);
            printf("%lld\n", part.query(left - 1, right - 1).sum);
        }
    }

    return 0;
}
```
