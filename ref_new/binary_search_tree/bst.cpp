#if 1

#include <cstdio>
#include <malloc.h>

struct Data {
    int key, value;
};

template<typename Type>
struct BST {
    struct TreeNode {
        Type data;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;

private:
    TreeNode* new_node(const Type& data) {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->data = data;
        node->left = node->right = nullptr;
        return node;
    }
    TreeNode* insert_node(TreeNode* node, const Type& data) {
        if (node == nullptr) { return new_node(data); }
        if (data.key < node->data.key) { node->left = insert_node(node->left, data); }
        else { node->right = insert_node(node->right, data); }
        return node;
    }
    TreeNode* find_node(TreeNode* node, int key) {
        if (node == nullptr) { return node; }
        if (key == node->data.key) { return node ; }
        else if (key < node->data.key) { return find_node(node->left, key); }
        else if (node->data.key < key) { return find_node(node->right, key); }
    }
    TreeNode* inorder_node(TreeNode* node) {
        if (node == nullptr) { return node; }
        inorder_node(node->left);
        printf("(%d [%d]) ", node->data.key, node->data.value);
        inorder_node(node->right);
    }
    TreeNode* top_node(TreeNode* node) {
        if (node == nullptr) { return node; }
        while (node->right != nullptr) { node = node->right; }
        return node;
    }
    TreeNode* bottom_node(TreeNode* node) {
        if (node == nullptr) { return node; }
        while (node->left != nullptr) { node = node->left; }
        return node;
    }

public:
    void clear() { root = nullptr; }
    void insert(const Type& data) {
        //if (root == nullptr) { root = insert_node(root, data); }
        //insert_node(root, data);
        root = insert_node(root, data);
    }
    int find(int key) {
        TreeNode* node = find_node(root, key);
        if (node != nullptr) { return node->data.value; }
        return -1;
    }
    void inorder() {
        if (root != nullptr) {
            inorder_node(root);
            printf("\n");
        }
    }
    Type top() { return top_node(root)->data; }
    Type bottom() { return bottom_node(root)->data; }
    bool empty() { return root == nullptr; }
};
BST<Data> bst;

int main()
{
    bst.clear();
    printf("Find(key = 11): value = %d\n", bst.find(11));
    printf("Find(key = 20): value = %d\n", bst.find(20));

    bst.insert({ 12, 0 });
    bst.insert({ 10, 1 });
    bst.insert({ 20, 2 });
    bst.insert({ 8, 3 });
    bst.insert({ 11, 4 });
    bst.insert({ 15, 5 });
    bst.insert({ 28, 6 });
    bst.insert({ 4, 7 });
    bst.insert({ 2, 8 });

    bst.inorder();

    Data top = bst.top(), bottom = bst.bottom();
    printf("Max.: key = %d, value = %d\n", top.key, top.value);
    printf("Min.: key = %d, value = %d\n", bottom.key, bottom.value);

    printf("Find(key = 11): value = %d\n", bst.find(11));
    printf("Find(key = 20): value = %d\n", bst.find(20));

    bst.inorder();


    return 0;
}
#endif