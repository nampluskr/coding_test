#if 0
// [포인트 값]
#include <vector>
#include <cmath>
using namespace std;

struct Partition {
    vector<int> buckets;
    vector<int> values;
    int N;      // bucket size

    void init(int num_values) {
        N = sqrt(num_values);
        int num_buckets = ceil((double)num_values / N);
        buckets.clear();    buckets.resize(num_buckets);
        values.clear();     values.resize(num_values);
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { values[i] += value; }
            return;
        }

        while (left / N == s) { values[left++] += value; }
        while (right / N == e) { values[right--] += value; }
        for (int i = s + 1; i <= e - 1; i++) { buckets[i] += value; }
    }
    int query(int idx) {
        return values[idx] + buckets[idx / N];
    }
};
Partition part;

int main()
{
    int num_values = 19;
    part.init(num_values);

    part.update(1, 6, 5);
    part.update(4, 13, 2);
    part.update(6, 10, -1);
    part.update(3, 17, 3);
    part.update(2, 3, -2);
    part.update(10, 12, 5);

    for (int i = 0; i < num_values; i++)
        printf("%d ", part.query(i));
    printf("\n");

    return 0;
}

#endif