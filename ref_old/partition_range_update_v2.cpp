#if 1
// [STL] Range Update
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
    int base;
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
            buckets[i].base += value;
            buckets[i].top += value;
            buckets[i].bot += value;
            buckets[i].sum += value * N;
        }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N].base;
    }
    Data query() {
        Data ret = { 0, INF, 0 };

        for (int i = 0; i < num_buckets ; i++) {
            ret.top = max(ret.top, buckets[i].top);
            ret.bot = min(ret.bot, buckets[i].bot);
            ret.sum += buckets[i].sum;
        }
        return ret;
    }
};
Partition part;

void print_query() {
    for (int i = 0; i < part.values.size(); i++)
        printf("%d ", part.query(i));
    printf("\n");

    Data ret = part.query();
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

    part.update(1, 6, 5);       print_query();
    part.update(4, 13, 2);      print_query();
    part.update(6, 10, -1);     print_query();
    part.update(3, 17, 3);      print_query();
    part.update(2, 3, -2);      print_query();
    part.update(10, 12, 5);     print_query();

    return 0;
}

#endif