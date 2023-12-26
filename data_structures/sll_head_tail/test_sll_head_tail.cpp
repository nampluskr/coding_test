#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include "sll_head_tail.h"

SLL<DATA> L;

void info(SLL<DATA>& L) {
    char status[50];
    if (!L.empty())
        sprintf(status, "[%s, n=%d, head=%d, tail=%d]", 
            "Filled", L.size(), L.head->data.value, L.tail->data.value);
    else
        sprintf(status, "[%s, n=%d, head=%s, tail=%s]", 
            "Empty", L.size(), "null", "null");
    printf("  %s: ", status);
    L.preorder(L.head);
    printf("\n");
}

void test_init() {
    printf("\n*** Initialize ***\n");
    L.clear();    info(L);
}

void test_push_back() {
    printf("\n*** Push Back ***\n");
    L.push_back({ 20, 2 });  info(L);
    L.push_back({ 10, 1 });  info(L);
    L.push_back({ 30, 3 });  info(L);
    L.push_back({ 40, 4 });  info(L);
    L.push_back({ 50, 5 });  info(L);
}

void test_push_front() {
    printf("\n*** Push Back ***\n");
    L.push_front({ 20, 2 });  info(L);
    L.push_front({ 10, 1 });  info(L);
    L.push_front({ 30, 3 });  info(L);
    L.push_front({ 40, 4 });  info(L);
    L.push_front({ 50, 5 });  info(L);
}

void test_remove() {
    printf("\n*** Remove ***\n");
    L.remove({ 30, 3 });  info(L);
    L.remove({ 20, 2 });  info(L);
    L.remove({ 40, 4 });  info(L);
    L.remove({ 10, 1 });  info(L);
    L.remove({ 50, 5 });  info(L);
}

int main()
{
    test_init();
    test_push_back();
    //test_push_front();
    //test_remove();

    for (auto ptr = L.head; ptr != nullptr; ptr = ptr->next)
        printf("%d[%d]->", ptr->data.value, ptr->data.idx);
    printf("\n");

    auto ptr = L.head;
    while (ptr != nullptr) {
        printf("%d[%d]->", ptr->data.value, ptr->data.idx);
        ptr = ptr->next;
    }
    printf("\n");

    

    return 0;
}