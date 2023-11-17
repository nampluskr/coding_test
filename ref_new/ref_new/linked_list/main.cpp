#include <cstdio>
#include "list.h"

LinkedList<int> L;
Stack<int> S;
Queue<int> Q;

int main()
{
    // test linked list
    L.clear();
    L.push_back(0);
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    printf("\n[List] size = %d\n", L.size());
    print_list(L);

    // test stack
    S.clear();
    S.push(0);
    S.push(1);
    S.push(2);
    S.push(3);

    printf("\n[Stack] size = %d\n", S.size());
    //print_list(S.lst);
    while (!S.empty()) {
        auto data = S.top(); S.pop();
        printf("[%d] size = %d\n", data, S.size());
    }

    // test stack
    Q.clear();
    Q.push(0);
    Q.push(1);
    Q.push(2);
    Q.push(3);

    printf("\n[Queue] size = %d\n", Q.size());
    //print_list(Q.lst);
    while (!Q.empty()) {
        auto data = Q.front(); Q.pop();
        printf("[%d] size = %d\n", data, Q.size());
    }


    return 0;
}