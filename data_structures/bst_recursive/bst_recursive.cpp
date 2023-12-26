#if 1
#include <cstdio>
#include "bst_recursive.h"

using NODE = BST<DATA>::NODE;

// 기본 연산
NODE* BST<DATA>::clear(NODE* ptr) {
    // base case
    if (ptr == nullptr) { return nullptr; }
    // postorder traversal
    ptr->left = clear(ptr->left);
    ptr->right = clear(ptr->right);
    // visit the parent
    delete_node(ptr);
    return nullptr;
}

NODE* BST<DATA>::insert(NODE* ptr, const DATA& data) {
    // No base case
    // visit the parent
    if (ptr == nullptr) { return new_node(data); }
    // postorder traversal
    if (data < ptr->data) { ptr->left = insert(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = insert(ptr->right, data); }
    return ptr;     // 입력 받은 시작 포인터 반환
}

void BST<DATA>::inorder(NODE* ptr) {
    if (ptr == nullptr) { return; }
    inorder(ptr->left);
    printf("%d[%d] ", ptr->data.value, ptr->data.idx);
    inorder(ptr->right);
}

NODE* BST<DATA>::find(NODE* ptr, const DATA& data) {
    // base case
    if (ptr == nullptr) { return nullptr; }
    // visit the parent
    if (ptr->data == data) { return ptr; }
    // postorder traversal
    if (data < ptr->data) return find(ptr->left, data);
    else if (ptr->data < data) return find(ptr->right, data);
}

// recursive
NODE* BST<DATA>::find_min(NODE* ptr) {
    if (ptr->left == nullptr) { return ptr; }
    return find_min(ptr->left);
}

NODE* BST<DATA>::find_max(NODE* ptr) {
    if (ptr->right == nullptr) { return ptr; }
    return find_max(ptr->right);
}

// https://srdeveloper.tistory.com/26?utm_source=pocket_saves
// preorder traversal
NODE* BST<DATA>::remove(NODE* ptr, const DATA& data) {
    // base case
    if (ptr == nullptr) return nullptr;
    // visit the node in preorder
    if (ptr->data == data) {
        printf("%d[%d] ", ptr->data.value, ptr->data.idx);
        NODE* target = ptr;
        if (!ptr->left && !ptr->right) { ptr = nullptr; }
        else if (ptr->left && !ptr->right) { ptr = ptr->left; }
        else if (!ptr->left && ptr->right) { ptr = ptr->right; }
        else {
            NODE* min_node = find_min(ptr->right);
            ptr->right = ptr->right->right;
            min_node->left = target->left;
            min_node->right = target->right;
            ptr = min_node;
        }
        delete_node(target);
        return ptr;
    }
    if (data < ptr->data) { ptr->left = remove(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = remove(ptr->right, data); }
    return ptr;
}

// c언어로 쉽게 풀어쓴 자료구조 천인국/공용해/하상호 생능출판사
// postorder traversal
//NODE* BST<DATA>::remove(NODE* ptr, const DATA& data) {
//    if (ptr == nullptr) return nullptr;
//    if (data < ptr->data) ptr->left = remove(ptr->left, data);
//    else if (ptr->data < data) ptr->right = remove(ptr->right, data);
//    else { // data == ptr->data
//        printf("%d[%d] ", ptr->data.value, ptr->data.idx);
//        if (ptr->left == nullptr) {         // 자식 노드가 없을 때 리프 노드
//            NODE* temp = ptr->right;
//            delete_node(ptr);
//            return temp;
//        }
//        else if (ptr->right == nullptr) {   // 자식 노드가 하나만 가지고 있을 때
//            NODE* temp = ptr->left;
//            delete_node(ptr);
//            return temp;
//        }
//        else {                              // 자식 노드가 2개의 노드를 가지고 있을 때
//            NODE* temp = find_min(root->right);
//            ptr->data = temp->data;
//            ptr->right = remove(ptr->right, temp->data);
//        }
//    }
//    return ptr;
//}

#endif