#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include "bst_recursive.h"

BST<DATA> bst;

void info(BST<DATA>& bst) {
    char status[50];
    if (!bst.empty())
        sprintf(status, "[%s, n=%d, root=%d]", "Filled", bst.size(), bst.root->data.value);
    else
        sprintf(status, "[%s, n=%d, root=%s]", "Empty", bst.size(), "null");
    printf(">> %s: ", status);
    bst.inorder(bst.root);
    printf("\n");
}

void test_init() {
    printf("\n*** Initialize ***\n");
    bst.root = bst.clear(bst.root); info(bst);
}

void test_insert() {
    printf("\n*** Insert ***\n");
    bst.root = bst.insert(bst.root, { 20, 2 }); info(bst);
    bst.root = bst.insert(bst.root, { 10, 1 }); info(bst);
    bst.root = bst.insert(bst.root, { 30, 3 }); info(bst);
    bst.root = bst.insert(bst.root, { 40, 4 }); info(bst);
    bst.root = bst.insert(bst.root, { 50, 5 }); info(bst);
}

void test_remove() {
    printf("\n*** Remove ***\n");
    bst.root = bst.remove(bst.root, { 20, 2 }); info(bst);
    bst.root = bst.remove(bst.root, { 10, 1 }); info(bst);
    bst.root = bst.remove(bst.root, { 30, 3 }); info(bst);
    bst.root = bst.remove(bst.root, { 50, 5 }); info(bst);
    bst.root = bst.remove(bst.root, { 40, 4 }); info(bst);
}

int main()
{
    test_init();
    test_insert();
    //test_init();
    test_remove();

    return 0;
}
#endif