#include <cstdio>
#include "heap.h"

PQ<int, 10> Q;

int main()
{
    Q.clear();
    Q.push(10);
    Q.push(20);
    Q.push(30);
    Q.push(40);
    Q.push(50);

    while (!Q.empty()) {
        int top = Q.top(); Q.pop();
        printf(">> Popped: %d\n", top);
    }

    return 0;
}