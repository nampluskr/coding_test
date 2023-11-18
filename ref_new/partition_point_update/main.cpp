#include <cstdio>
#include <cmath>
#include "part.h"

#define MINMAX

PartitionPoint part;

extern int num_values;
extern int bucket_size;
extern int num_buckets;

int main()
{
    int values[ ] = { 1, 4, 7, 5, 2, 8, 3, 1, 8, 5, 4, 7, 2, 7, 3, 0 };

    num_values = 16;
    bucket_size = sqrt(num_values);
    num_buckets = ceil((double)num_values / bucket_size);

    part.init();
    for ( int i = 0; i < num_values; i++ ) { part.update(i, values[i]); }

#ifndef MINMAX
    // range sum
    auto ret = part.query(3, 14);
    printf(">> Range Sum = %d\n", ret);

#else
    // range min, max
    auto ret = part.query(4, 8);
    printf(">> Range Max = %d: values[%d]\n", ret.top.value, ret.top.idx);
    printf(">> Range Min = %d: values[%d]\n", ret.bot.value, ret.bot.idx);

#endif

    return 0;
}