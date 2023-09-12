#if 1
// [STL] point update / range query
#include <vector>
#include <cmath>
using namespace std;

int num_values;
int bucket_size;        // sqrt(num_values)
int num_buckets;        // ceil((double)num_values / bucket_size)

struct Partition {
    vector<int> buckets;
    vector<int> values;
    int N;      // bucket size

    void init() {
        N = bucket_size;
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update(int idx, int value) {
        buckets[idx / N] -= values[idx];
        values[idx] += value;
        buckets[idx / N] += value;
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
        while (right / N == e) { ret += values[right--]; }
        for (int i = s + 1; i <= e - 1; i++) { ret += buckets[i]; }
        return ret;
    }
};
Partition part;


int main()
{
    num_values = 16;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);

    part.init();
    vector<int> x = { 1, 4, 7, 5, 2, 8, 3, 1, 8, 5, 4, 7, 2, 7, 3, 0 };

    for (int i = 0; i < x.size(); i++) {
        part.update(i, x[i]);
    }
    int ret = part.query(3, 14);
    printf("Range sum = %d\n", ret);

    return 0;
}
#endif