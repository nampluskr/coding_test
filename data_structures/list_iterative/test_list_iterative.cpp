#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include "list_iterative.h"

LIST<DATA> lst;

void info(LIST<DATA>& lst) {
    char status[50];
    if (!lst.empty())
        sprintf(status, "[%s, n=%d, head=%d]", "Filled", lst.size(), lst.head->data.value);
    else
        sprintf(status, "[%s, n=%d, head=%s]", "Empty", lst.size(), "null");
    printf("  %s: ", status);
    lst.preorder();
    printf("\n");
}

void test_init() {
    printf("\n*** Initialize ***\n");
    lst.clear();    info(lst);
}

void test_insert() {
    printf("\n*** Insert ***\n");
    lst.insert({ 20, 2 });  info(lst);
    lst.insert({ 10, 1 });  info(lst);
    lst.insert({ 30, 3 });  info(lst);
    lst.insert({ 40, 4 });  info(lst);
    lst.insert({ 50, 5 });  info(lst);
}

void test_delete() {
    printf("\n*** Remove ***\n");
    lst.remove({ 30, 3 });  info(lst);
    lst.remove({ 20, 2 });  info(lst);
    lst.remove({ 40, 4 });  info(lst);
    lst.remove({ 10, 1 });  info(lst);
    lst.remove({ 50, 5 });  info(lst);
}

int main()
{
    //test_init();
    test_insert();
    //test_delete();

    lst.clear(); info(lst);

    //printf("\n*** Find ***\n");
    //LIST<DATA>::NODE* ptr;
    //ptr = lst.find({ 30, 3 });
    //if (ptr == nullptr) { printf(">> Not found.\n"); }
    //else { printf( ">> Found: % d[% d]\n", ptr->data.value, ptr->data.idx); }



    return 0;
}
#endif