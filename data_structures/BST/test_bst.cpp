#if 0
#include "bst.h"

BST<DATA> bst;

void init() {
    bst.insert({ 20, 2 });
    bst.insert({ 10, 1 });
    bst.insert({ 30, 3 });
    bst.insert({ 40, 4 });
    bst.insert({ 50, 5 });
}

int main()
{
    init();
    bst.print();

    bst.root = bst.remove(bst.root, { 40, 4 });
    bst.print();

    return 0;
}
#endif