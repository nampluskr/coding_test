#if 0
#include "bst.h"

using NODE = BST<DATA>::NODE;

// 기본 멤버 함수
NODE* BST<DATA>::new_node(const DATA& data) {
    //NODE* ptr = new NODE{ data, nullptr, nullptr };
    NODE* ptr = new NODE;
    ptr->data = data;
    ptr->left = ptr->right = nullptr;
    return ptr;
}

NODE* BST<DATA>::insert_node(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) { return new_node(data); }
    if (data < ptr->data) { ptr->left = insert_node(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = insert_node(ptr->right, data); }
    return ptr;    // root 노드 반환
}

void BST<DATA>::insert(const DATA& data) {
    root = insert_node(root, data);
    treeSize += 1;
}

NODE* BST<DATA>::find(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) { return nullptr; }
    // preorder
    if (data == ptr->data) { return ptr; }
    if (data < ptr->data) { return find(ptr->left, data); }
    else if (ptr->data < data) { return find(ptr->right, data); }
}

NODE* BST<DATA>::find(const DATA& data) {
    NODE* ptr = root;
    while (ptr != nullptr) {
        if (ptr->data == data) { return ptr; }
        if (data < ptr->data) { ptr = ptr->left; }
        else if (ptr->data < data) { ptr = ptr->right; }
    }
    return nullptr;
}

void BST<DATA>::clear() {
}

// 추가 멤버 함수
DATA BST<DATA>::top() {
    if (root) {
        NODE* ptr = root;
        while (ptr->right) { ptr = ptr->right; }
        return ptr->data;
    }
}

DATA BST<DATA>::bottom() {
    if (root) {
        NODE* ptr = root;
        while (ptr->left) { ptr = ptr->left; }
        return ptr->data;
    }
}

// 보조 멤버 함수
NODE* BST<DATA>::inorder(NODE* ptr) {
    if (ptr == nullptr) { return ptr; }
    inorder(ptr->left);
    printf("(%d [%d]) ", ptr->data.value, ptr->data.idx);
    inorder(ptr->right);
}

void BST<DATA>::print() {
    printf(">> ");
    inorder(root);
    printf("\n");
}

NODE* FindMinNode(NODE* ptr, NODE** min_node)
{
    if (ptr->left == nullptr)
    {
        *min_node = ptr;
        ptr = ptr->right;
        return ptr;
    }
    else
    {
        ptr->left = FindMinNode(ptr->left, min_node);
        return ptr;
    }
}

NODE* remove(NODE* ptr, const DATA& data)
{
    if (ptr == nullptr) return nullptr;

    if (ptr->data == data)
    {
        NODE* deleteNode = ptr;
        if (ptr->left == nullptr && ptr->right == nullptr)
        {
            ptr = nullptr;
        }
        else if (ptr->left != nullptr && ptr->right == nullptr)
        {
            ptr = ptr->left;
        }
        else if (ptr->left == nullptr && ptr->right != nullptr)
        {
            ptr = ptr->right;
        }
        else
        {
            NODE* min_node = nullptr;
            ptr->right = FindMinNode(ptr->right, &min_node);
            min_node->left = deleteNode->left;
            min_node->right = deleteNode->right;
            ptr = min_node;
        }

        delete deleteNode;
        return ptr;
    }
    else
    {
        if (data < ptr->data)
        {
            ptr->left = remove(ptr->left, data);
        }
        else
        {
            ptr->right = remove(ptr->right, data);
        }

        return ptr;
    }
}
#endif