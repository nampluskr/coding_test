#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include "list_recursive.h"

LIST<DATA> lst;

void info(LIST<DATA>& lst) {
    char status[50];
    if (!lst.empty())
        sprintf(status, "[%s, n=%d, head=%d]", "Filled", lst.size(), lst.head->data.value);
    else
        sprintf(status, "[%s, n=%d, head=%s]", "Empty", lst.size(), "null");
    printf("  %s: ", status);
    lst.preorder(lst.head);
    printf("\n");
}

void test_init() {
    printf("\n*** Initialize ***\n");
    lst.head = lst.clear(lst.head); info(lst);
}

void test_insert() {
    printf("\n*** Insert ***\n");
    lst.head = lst.insert(lst.head, { 20, 2 }); info(lst);
    lst.head = lst.insert(lst.head, { 10, 1 }); info(lst);
    lst.head = lst.insert(lst.head, { 30, 3 }); info(lst);
    lst.head = lst.insert(lst.head, { 40, 4 }); info(lst);
    lst.head = lst.insert(lst.head, { 50, 5 }); info(lst);
}

void test_delete() {
    printf("\n*** Remove ***\n");
    lst.head = lst.remove(lst.head, { 30, 3 }); info(lst);
    lst.head = lst.remove(lst.head, { 20, 2 }); info(lst);
    lst.head = lst.remove(lst.head, { 40, 4 }); info(lst);
    lst.head = lst.remove(lst.head, { 10, 1 }); info(lst);
    lst.head = lst.remove(lst.head, { 50, 5 }); info(lst);
}

int main()
{
    //test_init();
    test_insert();

    lst.head = lst.clear(lst.head); info(lst);

    //test_delete();

    return 0;
}
#endif