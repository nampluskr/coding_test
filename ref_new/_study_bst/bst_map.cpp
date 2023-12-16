#if 1
// Map using binary search tree
#include <cstdio>

template<typename Key, typename Value = int>
struct Map {
private:
    // TreeNode : TreeNode<Key, Value>
    struct TreeNode {
        Key key;
        Value value;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    int mapSize;

    TreeNode* new_node(const Key& key, const Value& value) {
        TreeNode* node = new TreeNode;
        node->key = key;
        node->value = value;
        node->left = node->right = nullptr;
        return node;
    }
    TreeNode* insert_node(TreeNode* node, const Key& key, const Value& value) {
        if (node == nullptr) { return new_node(key, value); }
        else if (key < node->key) { node->left = insert_node(node->left, key, value); }
        else if (node->key < key) { node->right = insert_node(node->right, key, value); }
        return node;
    }
    TreeNode* find_node(TreeNode* node, const Key& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else if (key < node->key) { return find_node(node->left, key); }
        else if (node->key < key) { return find_node(node->right, key); }
    }
    TreeNode* inorder_node(TreeNode* node) {
        if (node == nullptr) { return nullptr; }
        inorder_node(node->left);
        printf("([%d], %d) ", node->key, node->value);
        inorder_node(node->right);
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

public:
    void clear() { root = nullptr; mapSize = 0; }
    void insert(const Key& key, const Value& value) { 
        root = insert_node(root, key, value);
        mapSize++;
    }
    void inorder() {
        if (root != nullptr) {
            inorder_node(root);
            printf("\n");
        }
    }
    bool empty() { return mapSize == 0; }
    int size() { return mapSize; }
    Value find(const Key& key) {
        auto node = find_node(root, key);
        if (node != nullptr) { return node->value; }
        return -1;      // Value() 초기화된 객체
    }
    Value operator[](const Key& key) { return find(key); }
    Value top() { return max_node(root)->value; }
    Value bottom() { return min_node(root)->value; }
};

Map<int, int> map;

int main()
{
    map.clear();
    map.insert(20, 0);
    map.insert(10, 1);
    map.insert(30, 2);
    map.insert(40, 3);
    map.insert(50, 4);

    map.inorder();
    printf(">> find(50): %d\n", map.find(50));
    printf(">> find(90): %d\n", map.find(90));
    printf(">> map[50]: %d\n", map[50]);
    printf(">> map[90]: %d\n", map[90]);


    return 0;
}
#endif