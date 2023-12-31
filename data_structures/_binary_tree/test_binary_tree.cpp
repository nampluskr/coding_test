#include <cstdio>
#include "binary_tree.h"

BinaryTree<int> bt;
Node<int>* root;

/*
            10
        6       12
     4    8         15
                 14    20
*/

void init() {
    Node<int>* n1 = bt.new_node(4, nullptr, nullptr);
    Node<int>* n2 = bt.new_node(8, nullptr, nullptr);
    Node<int>* n3 = bt.new_node(6, n1, n2);
    Node<int>* n4 = bt.new_node(14, nullptr, nullptr);
    Node<int>* n5 = bt.new_node(20, nullptr, nullptr);
    Node<int>* n6 = bt.new_node(15, n4, n5);
    Node<int>* n7 = bt.new_node(12, nullptr, n6);

    root = bt.new_node(10, n3, n7);
}

void test_traserval() {
    printf("\n*** Preorder Traversal ***\n");
    printf(">> ");
    preorder(root);  printf("\n");

    printf("\n*** Preorder Order Traversal (Iterative) ***\n");
    printf(">> ");
    preorder_iterative(root); printf("\n");

    printf("\n*** Inorder Traversal ***\n");
    printf(">> ");
    inorder(root);   printf("\n");

    printf("\n*** Postorder Traversal ***\n");
    printf(">> ");
    postorder(root); printf("\n");

    printf("\n*** Level Order Traversal ***\n");
    printf(">> ");
    level_order(root); printf("\n");
}


int main()
{
    init();

    printf(">> Count  = %d\n", count_nodes<int>(root));
    printf(">> Sum    = %d\n", sum_nodes<int>(root));
    printf(">> Height = %d\n", height_tree<int>(root));
    printf(">> Leaves = %d\n", leaf_nodes<int>(root));

    return 0;
}
