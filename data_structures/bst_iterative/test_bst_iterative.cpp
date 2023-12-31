#include <cstdio>
#include "bst_iterative.h"
//#include <queue>
//#include <stack>
//using namespace std;

BinaryTree<int> bt;
Node<int>* root;

void preorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    printf("[%d]->", ptr->data);    // visit the node
    preorder(ptr->left);
    preorder(ptr->right);
}

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    inorder(ptr->left);
    printf("[%d]->", ptr->data);    // visit the node
    inorder(ptr->right);
}

void postorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    postorder(ptr->left);
    postorder(ptr->right);
    printf("[%d]->", ptr->data);    // visite the node
}

void preorder_iterative(Node<int>* ptr) {
    Stack<Node<int>*> S;
    S.push(ptr);

    while (!S.empty()) {
        ptr = S.top(); S.pop();

        printf("[%d]->", ptr->data);    // visite the node
        if (ptr->right != nullptr) { S.push(ptr->right); }
        if (ptr->left != nullptr) { S.push(ptr->left); }
    }
}

void level_order(Node<int>* ptr) {
    Queue<Node<int>*> Q;
    Q.push(ptr);

    while (!Q.empty()) {
        ptr = Q.front(); Q.pop();

        printf("[%d]->", ptr->data);    // visite the node
        if (ptr->left != nullptr)
            Q.push(ptr->left);
        if (ptr->right != nullptr)
            Q.push(ptr->right);
    }
}

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

/*
            10
        6       12
     4    8         15
                 14    20
*/


int main()
{
    init();

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

    return 0;
}