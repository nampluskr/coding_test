#include <cstdio>
#include "stack_queue.h"

Stack<int> S;
Queue<int> Q;

void test_stack() {
    printf("\n *** Stack ***\n");
    S.clear();
    S.push(10);
    S.push(20);
    S.push(30);
    S.push(40);
    S.push(50);

    while (!S.empty()) {
        int top = S.top(); S.pop();
        printf(">> Popped: %d\n", top);
    }
}

void test_queue() {
    printf("\n *** Queue ***\n");
    Q.clear();
    Q.push(10);
    Q.push(20);
    Q.push(30);
    Q.push(40);
    Q.push(50);

    while (!Q.empty()) {
        int front = Q.front(); Q.pop();
        printf(">> Popped: %d\n", front);
    }
}

int main()
{
    test_stack();
    test_queue();

    return 0;
}