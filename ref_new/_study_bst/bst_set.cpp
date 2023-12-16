#if 0
// Set using binary search tree
#include <cstdio>

template<typename Key>
struct Set {
private:
    // TreeNode : TreeNode<Key>
    struct TreeNode {
        Key key;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    int setSize;

    TreeNode* new_node(const Key& key) {
        TreeNode* node = new TreeNode;
        node->key = key;
        node->left = node->right = nullptr; 
        return node;
    }
    TreeNode* insert_node(TreeNode* node, const Key& key) {
        if (node == nullptr) { return new_node(key); }
        else if (key < node->key) { node->left = insert_node(node->left, key); }
        else if (node->key < key) { node->right = insert_node(node->right, key); }
        return node;
    }
    TreeNode* find_node(TreeNode* node, const Key& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else if (key < node->key) { return find_node(node->left, key); }
        else if (node->key < key) { return find_node(node->right, key); }
    }
    TreeNode* min_node(TreeNode* node) {
        if (node == nullptr) { return nullptr; }
        else if (node->left == nullptr) { return node->value; }
        return min_node(node->left);
    }
    TreeNode* max_node(TreeNode* node) {
        if (node == nullptr) { return nullptr; }
        else if (node->right == nullptr) { return node->value; }
        return max_node(node->right);
    }
    TreeNode* inorder_node(TreeNode* node) {
        if (node == nullptr) { return nullptr; }
        inorder_node(node->left);
        printf("[%d] ", node->key);
        inorder_node(node->right);
    }

public:
    void clear() { root = nullptr; setSize = 0; }
    void insert(const Key& key) { 
        root = insert_node(root, key);
        setSize++;
    }
    bool find(const Key& key) {
        auto node = find_node(root, key);
        if (node != nullptr) { return true; }
        return false;
    }
    void inorder() {
        if (root != nullptr) {
            inorder_node(root);
            printf("\n");
        }
    }
    bool empty() { return setSize == 0; }
    int size() { return setSize; }
    Key top() { return max_node(root)->key; }
    Key bottom() { return min_node(root)->key; }
};

Set<int> set;

int main()
{
    set.clear();
    set.insert(20);
    set.insert(10);
    set.insert(30);
    set.insert(40);
    set.insert(50);

    set.inorder();

    printf(">> find(10): %d\n", set.find(10));
    printf(">> find(90): %d\n", set.find(90));

    set.insert(50);
    set.inorder();

    return 0;
}
#endif