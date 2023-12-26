#if 0
#include <cstdio>

template<typename DATA>
struct SLL {
    struct NODE {
        DATA data;
        NODE* next;
    };
    NODE* head;
    int listSize;

    SLL() { head = nullptr; listSize = 0; }
    void clear() { clear(head); }
    void clear(NODE* node) { 
        if (node == nullptr) return;
        clear(node->next);
        printf(">> delete { %d, %d } \n", node->data.value, node->data.idx);
        delete node;
        listSize -= 1;
    }
    void push_front(const DATA& data) {
        NODE* node = new NODE{ data, nullptr };
        if (head == nullptr) { head = node; }
        else { node->next = head; head = node; }
        listSize++;
    }
    void pop_front() {
        NODE* tmp = head;
        head = head->next;
        delete tmp;
        listSize--;
    }
    bool empty() { return listSize == 0; }  // return head == nullptr;
    int size() { return listSize; }
};

struct DATA {
    int value, idx;

    bool operator==(const DATA& data) const {
        return value == data.value;
    }
    bool operator<(const DATA& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

void test_sll() {
    SLL<DATA> sll;
    sll.clear();
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());

    sll.push_front({ 10, 1 });
    sll.push_front({ 20, 2 });
    sll.push_front({ 30, 3 });
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());

    if (!sll.empty()) {
        for (auto node = sll.head; node; node = node->next)
            printf("{ %d, %d }, ", node->data.value, node->data.idx);
        printf("\n");
    }
    sll.clear(sll.head);
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());
}

//void test_sll_list() {
//    SLL<SLL<DATA>> sllList;
//    sllList.clear();
//
//
//}

int main() {
    test_sll();
}
#endif