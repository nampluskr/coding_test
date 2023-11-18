#include <cstdio>
#include "list.h"

void print_list(const LinkedList<int>& lst) {
    for (auto ptr = lst.head; ptr; ptr = ptr->next) {
        printf("[%d]", ptr->data);
        if (ptr != lst.tail) { printf("-"); }
    }
    printf("\n");
}