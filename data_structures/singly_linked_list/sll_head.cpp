#if 0
#include <forward_list>
using namespace std;

template<typename KEY, typename VALUE>
struct SinglyLinkedList {
    struct NODE {
        KEY key;
        VALUE value;
        NODE* next;
    };
    NODE* head;
    int listSize;

    NODE* new_node(const KEY& key, const VALUE& value) {
        NODE* node = new NODE;
        node->key = key;
        node->value = value;
        node->next = nullptr;
        return node;
    }
    NODE* emplace_node(NODE* node, const KEY& key, const VALUE& value) {
        if (node == nullptr) { return new_node(key, value); }
        else { node->next = emplace_node(node->next, key, value); }
        return node;
    }
    NODE* find_node(NODE* node, const KEY& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else { return find_node(node->next, key); }
    }

    void clear() { head = nullptr; listSize = 0; }
    void emplace(const KEY& key, const VALUE& value) { 
        head = emplace_node(head, key, value);
        listSize++;
    }
    NODE* insert(const KEY& key, const VALUE& value) {
        NODE* node = new_node(key, value);
        if (head == nullptr) { head = node; }
        else {
            NODE* tail = head;
            while (tail->next != nullptr) { tail = tail->next; }
            tail->next = node;
        }
        listSize++;
        return node;
    }
    NODE* find(const KEY& key) { return find_node(head, key); }
    VALUE& operator[](const KEY& key) {
        NODE* node = find(key);
        if (node == nullptr) { node = insert(key, {}); }
        return node->value;
    }
    bool empty() { return listSize == 0; }
    int size() { return listSize; }
};

template<typename Type>
void print(const Type& list) {
    if (list.head != nullptr) {
        auto node = list.head;
        for (; node->next; node = node->next)
            printf("([%d], %d) -> ", node->key, node->value);
        printf("([%d], %d)\n", node->key, node->value);
    }
}

void test_sll() {
    SinglyLinkedList<int, int> sll;
    sll.clear();

    sll.insert(10, 100);
    sll.insert(20, 200);
    sll.insert(30, 300);
    print(sll);
}

void test_sll_intMap() {
    SinglyLinkedList<int, int> intMap;
    intMap.clear();

    intMap[1] = 100;
    intMap[2] = 200;
    intMap[3] = 300;
    print(intMap);

    intMap.emplace(10, 1000);
    intMap.emplace(20, 2000);
    intMap.emplace(30, 3000);
    print(intMap);

    printf(">> find(1): %d\n", intMap[1]);
    printf(">> find(10): %d\n", intMap[10]);
    printf(">> find(5): %d\n", intMap[5]);
}

void test_sll_listMap() {
    SinglyLinkedList<int, SinglyLinkedList<int, int>> listMap;
    listMap.clear();

    listMap[1].emplace(10, 100);
    listMap[1].emplace(20, 200);
    listMap[1].emplace(30, 300);

    print(listMap[1]);
    printf(">> listMap    Size = %d\n", listMap.size());
    printf(">> listMap[1] Size = %d\n", listMap[1].size());
}

int main()
{
    //test_sll();

    //test_sll_intMap();

    test_sll_listMap();

    return 0;
}
#endif