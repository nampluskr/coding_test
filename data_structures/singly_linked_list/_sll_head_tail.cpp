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
    NODE* tail;
    int listSize;

    NODE* new_node(const KEY& key, const VALUE& value) {
        NODE* node = new NODE;
        node->key = key;
        node->value = value;
        node->next = nullptr;
        return node;
    }
    NODE* find_node(NODE* node, const KEY& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else { return find_node(node->next, key); }
    }
    
    void clear() { head = nullptr; listSize = 0; }
    void push_back(const KEY& key, const VALUE& value) {
        NODE* node = new_node(key, value);
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        listSize++;
    }
    void push_front(const KEY& key, const VALUE& value) {
        NODE* node = new_node(key, value);
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        listSize++;
    }
    NODE* find(const KEY& key) { return find_node(head, key); }
    VALUE& operator[](const KEY& key) {
        NODE* node = find(key);
        if (node == nullptr) {
            push_back(key, {});
            node = tail;
        }
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

void test_sll_intMap() {
    SinglyLinkedList<int, int> intMap;
    intMap.clear();

    intMap.push_back(10, 1000);
    intMap.push_back(20, 2000);
    print(intMap);

    intMap.push_front(40, 4000);
    intMap.push_front(50, 5000);
    print(intMap);

    printf(">> [%d] -> %d\n", 10, intMap[10]);
    printf(">> [%d] -> %d\n", 50, intMap[50]);
}

void test_sll_listMap() {
    SinglyLinkedList<int, SinglyLinkedList<int, int>> listMap;
    listMap.clear();

    SinglyLinkedList<int, int>& subMap = listMap[1];
    printf(">> listMap Size = %d\n", listMap.size());
    printf(">> subMap  Size = %d\n", subMap.size());

    subMap.push_back(10, 100);
    subMap.push_back(20, 200);
    subMap.push_front(30, 300);

    print(subMap);
    printf(">> listMap Size = %d\n", listMap.size());
    printf(">> subMap  Size = %d\n", subMap.size());
}

int main()
{
    //test_sll_intMap();

    test_sll_listMap();

    return 0;
}
#endif