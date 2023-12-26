#if 1
#include <stdio.h>
#include <stdlib.h>

struct DATA {
    int value;
    int idx;

    DATA(int value = 0, int idx = -1) { this->value = value; this->idx = idx; }
    bool operator<(const DATA& data) const { 
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
    bool operator==(const DATA& data) const { 
        return value == data.value && idx == data.idx;
    }
};

template<typename DATA>
struct BST {
    struct NODE {
        DATA data;
        NODE* left;
        NODE* right; 
    };
    NODE* root;

    BST() { root = nullptr; }

    NODE* clear(NODE* ptr);
    NODE* insert(NODE* ptr, const DATA& data);
    NODE* find(NODE* ptr, const DATA& data);
    void inorder(NODE* ptr);

    NODE* find_min(NODE* ptr) {
        NODE* cur = ptr;
        while (cur->left != nullptr) { cur = cur->left; }
        return cur;
    }

    //NODE* find_min(NODE* ptr) {
    //    if (ptr->left == nullptr) { return nullptr; }
    //    ptr->left = find_min(ptr->left);
    //    return ptr;
    //}

    //NODE* find_min(NODE* ptr, NODE** min_node) {
    //    if (ptr->left == nullptr) {
    //        *min_node = ptr;
    //        ptr = ptr->right;
    //        return ptr;
    //    }
    //    ptr->left = find_min(ptr->left, min_node);
    //    return ptr;
    //}

    NODE* remove(NODE* ptr, const DATA& data) {
        if (ptr == nullptr) return nullptr;
        if (ptr->data == data) {
            NODE* target = ptr;
            if (!ptr->left && !ptr->right) { ptr = nullptr; }
            else if (ptr->left && !ptr->right) { ptr = ptr->left; }
            else if (!ptr->left && ptr->right) { ptr = ptr->right; }
            else {
                //NODE* min_node = nullptr;
                //ptr->right = find_min(ptr->right, &min_node);
                //min_node->left = target->left;
                //min_node->right = target->right;
                //ptr = min_node;

                NODE* min_node = find_min(ptr->right);
                ptr->right = ptr->right->right;
                min_node->left = target->left;
                min_node->right = target->right;
                ptr = min_node;
            }
            delete target;
            return ptr;
        }
        if (data < ptr->data) { ptr->left = remove(ptr->left, data); }
        else { ptr->right = remove(ptr->right, data); }
        return ptr;
    }
};

using NODE = BST<DATA>::NODE;

NODE* BST<DATA>::clear(NODE* ptr) {

    if (ptr == nullptr) return nullptr;
    ptr->left = clear(ptr->left);
    ptr->right = clear(ptr->right);

    // postorder (리프 노드부터 삭제)
    printf(">> Delete (%d, %d)\n", ptr->data.value, ptr->data.idx);
    delete ptr;
    return nullptr;
}

NODE* BST<DATA>::insert(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) {
        NODE* node = new NODE{ data, nullptr, nullptr };
        return node;
    }
    if (data < ptr->data) { ptr->left = insert(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = insert(ptr->right, data); }
    return ptr;
}

NODE* BST<DATA>::find(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) return nullptr;
    if (ptr->data == data) { return ptr; }
    if (data < ptr->data) { return find(ptr->left, data); }
    else { return find(ptr->right, data); }
}

void BST<DATA>::inorder(BST<DATA>::NODE* ptr) {
    if (ptr == nullptr) return;
    inorder(ptr->left);
    printf("%d ", ptr->data.value);
    inorder(ptr->right);
}

void main()
{
    BST<DATA> bst;

    bst.root = bst.insert(bst.root, { 20, 1 });
    bst.root = bst.insert(bst.root, { 10, 2 });
    bst.root = bst.insert(bst.root, { 32, 3 });
    bst.root = bst.insert(bst.root, { 4, 4 });
    bst.root = bst.insert(bst.root, { 13, 5 });
    bst.root = bst.insert(bst.root, { 25, 6 });
    bst.root = bst.insert(bst.root, { 55, 7 });
    bst.inorder(bst.root);  printf("\n");

    auto ptr = bst.find(bst.root, { 10, 2 });
    if (ptr)
        printf("%d\n", ptr->data.value);
    else
        printf("Not found.\n");

    bst.root = bst.remove(bst.root, { 32, 3 });
    bst.root = bst.remove(bst.root, { 25, 6 });
    bst.inorder(bst.root);  printf("\n");
    bst.inorder(bst.root);  printf("\n");

    bst.root = bst.clear(bst.root);
    //bst.inorder(bst.root);  printf("\n");
    
    ptr = bst.root;
}
#endif