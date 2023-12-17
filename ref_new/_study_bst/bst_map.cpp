#if 1
// Map using binary search tree
#include <cstdio>

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;
    int listSize;

    //LinkedList<Type>() { clear(); }
    ListNode* new_node(const Type& data) {
        ListNode* node = new ListNode;
        node->data = data;
        node->next = nullptr;
        return node;
    }
    void clear() { head = tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode* node = new_node(data);
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        listSize++;
    }
};

template<typename Key, typename Value = int>
struct Map {
private:
    // MapNode : MapNode<Key, Value>
    struct MapNode {
        Key key;
        Value value;
        MapNode* left;
        MapNode* right;
    };
    MapNode* root;
    int mapSize;

    MapNode* new_node(const Key& key, const Value& value) {
        MapNode* node = new MapNode;
        node->key = key;
        node->value = value;
        node->left = node->right = nullptr;
        return node;
    }
    MapNode* insert_node(MapNode* node, const Key& key, const Value& value) {
        if (node == nullptr) { return new_node(key, value); }
        else if (key < node->key) { node->left = insert_node(node->left, key, value); }
        else if (node->key < key) { node->right = insert_node(node->right, key, value); }
        return node;
    }
    MapNode* find_node(MapNode* node, const Key& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else if (key < node->key) { return find_node(node->left, key); }
        else if (node->key < key) { return find_node(node->right, key); }
    }
    MapNode* inorder_node(MapNode* node) {
        if (node == nullptr) { return nullptr; }
        inorder_node(node->left);
        printf("([%d], %d) ", node->key, node->value);
        inorder_node(node->right);
    }
    MapNode* min_node(MapNode* node) {
        if (node == nullptr) { return nullptr; }
        else if (node->left == nullptr) { return node->value; }
        return min_node(node->left);
    }
    MapNode* max_node(MapNode* node) {
        if (node == nullptr) { return nullptr; }
        else if (node->right == nullptr) { return node->value; }
        return max_node(node->right);
    }

public:
    void clear() { root = nullptr; mapSize = 0; }
    void emplace(const Key& key, const Value& value) { 
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
        MapNode* node = find_node(root, key);
        if (node == nullptr) { return { -1 }; }
        return node->value;
    }
    Value& operator[](const Key& key) {
        MapNode* node = find_node(root, key);
        if (node == nullptr) { 
            emplace(key, {});
            node = find_node(root, key);
        }
        return node->value;
    }
    Value top() { return max_node(root)->value; }
    Value bottom() { return min_node(root)->value; }
};

/////////////////////////////////////////////////////////////////////
void test_intMap() {
    Map<int, int> intMap;
    intMap.clear();

    //intMap[20] = 200;
    //intMap[10] = 100;
    //intMap[30] = 300;
    //intMap[40] = 400;
    //intMap[50] = 500;

    intMap.emplace(20, 200);
    intMap.emplace(10, 100);
    intMap.emplace(30, 300);
    intMap.emplace(40, 400);
    intMap.emplace(50, 500);

    intMap.inorder();
    printf(">> find(50): %d\n", intMap.find(50));
    printf(">> find(90): %d\n", intMap.find(90));
    printf(">> intMap[50]: %d\n", intMap[50]);
    printf(">> intMap[90]: %d\n", intMap[90]);
}

void test_listMap() {
    Map<int, LinkedList<int>> listMap;
    listMap.clear();

    //listMap.emplace(20, {});
    listMap[20].push_back(100);
    listMap[20].push_back(200);
    listMap[20].push_back(300);
}

int main()
{
    //test_intMap();

    test_listMap();

    return 0;
}
#endif