#if 1
// [STL] point update / range query
#include <vector>
#include <cmath>
using namespace std;

#define INF INT32_MAX

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

int num_values;
int bucket_size;        // sqrt(num_values)
int num_buckets;        // ceil((double)num_values / bucket_size)

struct Data {
    int top;
    int bot;
    int sum;

    void update(int value) {
        top = max(top, value);
        bot = min(bot, value);
        sum += value;
    }
};

struct Partition {
    vector<Data> buckets;
    vector<int> values;
    int N;      // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update_minmax(int bIdx) {
        int left = bIdx * N;
        int right = min((bIdx + 1) * N - 1, num_values - 1);

        buckets[bIdx].top = 0;
        buckets[bIdx].bot = INF;
        for (int i = left; i <= right; i++) {
            buckets[bIdx].top = max(buckets[bIdx].top, values[i]);
            buckets[bIdx].bot = min(buckets[bIdx].bot, values[i]);
        }
    }
    void update(int idx, int value) {
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
            for (int i = left; i <= right; i++) { ret.update(values[i]); }
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
    Data query() {
        return query(0, num_values - 1);
    }
};
Partition part;

void print_query(int left, int right) {
    for (int i = 0; i < part.values.size(); i++)
        printf("%d ", part.values[i]);
    printf("\n");

    Data ret = part.query(left, right);
    printf("values max = %d\n", ret.top);
    printf("values min = %d\n", ret.bot);
    printf("values sum = %d\n", ret.sum);
    printf("\n");
}


int main()
{
    num_values = 19;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);

    part.init();
    vector<int> x = { 0, 5, 3, 6, 10, 10, 9, 4, 4, 4, 9, 10, 10, 5, 3, 3, 3, 3, 0 };

    for (int i = 0; i < x.size(); i++) {
        part.update(i, x[i]);
    }

    print_query(0, 18);
    print_query(0, 3);
    print_query(3, 10);

    return 0;
}
#endif