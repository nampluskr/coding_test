#include <cstdio>
#include "partition.h"

PartitionSum P;

int main()
{
    int values[] = { 1, 4, 7, 5, 2, 8, 9, 1, 8, 5, 4, 7, 2, 7, 3, 0 };
    int num_values = 16;

    P.init(num_values);
    for (int i = 0; i < num_values; i++) { P.update(i, values[i]); }
    printf("sum(3, 14) = %d\n", P.query(3, 14));

    return 0;
}