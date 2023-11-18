#include <cstdio>
#include <cmath>
#include "part.h"

#define MINMAX

PartitionRange part;

extern int num_values;
extern int bucket_size;
extern int num_buckets;

int main()
{
    int values[] = { 1, 4, 7, 5, 2, 8, 3, 1, 8, 5, 4, 7, 2, 7, 3, 0 };

    num_values = 16;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);

    part.init();
    for (int i = 0; i < num_values; i++) {
        part.update(i, i, values[i]);
    }
    part.update(2, 14, 6);

#ifndef MINMAX
    // range sum
    auto ret = part.query(3, 8);
    printf(">> Range Sum = %2d\n", ret);

#else
    // range min, max
    auto ret = part.query(0, 15);
    printf(">> Range Max = %2d: values[%d]\n", ret.top.value, ret.top.idx);
    printf(">> Range Min = %2d: values[%d]\n", ret.bot.value, ret.bot.idx);

#endif

    return 0;
}