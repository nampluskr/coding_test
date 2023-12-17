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
    NODE* insert_node(NODE* node, const KEY& key, const VALUE& value) {
        if (node == nullptr) { return new_node(key, value); }
        return insert_node(node->next, key, value);
    }
    NODE* find_node(NODE* node, const KEY& key) {
        if (node == nullptr) { return nullptr; }
        else if (node->key == key) { return node; }
        else { return find_node(node->next, key); }

        //for (auto node = head; node; node = node->next)
        //    if (node->data == data)
        //        return node;
        //return nullptr;
    }

    void clear() { head = nullptr; listSize = 0; }
    void insert(const KEY& key, const VALUE& value) {
        if (head == nullptr) { head = new_node(key, value); return; }
        NODE* node = head;
        while (node->next != nullptr) { node = node->next; }
        node->next = new_node(key, value);
    }
    VALUE find(const KEY& key) {
        NODE* node = find_node(head, key);
        if (node == nullptr) { return {}; }
        return node->value;
    }
    VALUE& operator[](const KEY& key) {
        NODE* node = find_node(head, key);
        if (node == nullptr) { node = insert_node(head, key, {}); }
        return node->value;
    }
};
SinglyLinkedList<int, int> sll;

template<typename Type>
void print(const Type& list) {
    for (auto node = list.head; node; node = node->next)
        printf("([%d], %d) ", node->key, node->value);
    printf("\n");
}

int main()
{
    sll.clear();

    sll[1] = 100;
    sll[2] = 200;
    sll[3] = 300;

    //sll.insert(1, 100);
    //sll.insert(2, 200);
    //sll.insert(3, 300);

    print(sll);
    printf(">> find(1): %d\n", sll.find(1));
    printf(">> find(2): %d\n", sll.find(2));
    printf(">> find(5): %d\n", sll.find(5));

    return 0;
}
