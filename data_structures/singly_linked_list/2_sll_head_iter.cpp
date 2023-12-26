#if 1
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

    // O(1) 연산
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
    bool empty() { return head == nullptr; }  // return listSize == 0;
    int size() { return listSize; }
    void insert_after(NODE* cur, const DATA& data) {
        if (cur != nullptr) {
            NODE* node = new NODE{ data, nullptr };
            node->next = cur->next;
            cur->next = node;
        }
    }
    void erase_after(NODE* cur) {
        if (cur != nullptr && cur->next != nullptr) {
            NODE* tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
            //cur = cur->next;
        }
    }

    // O(n) 연산
    //void clear() {
    //    NODE* cur = head;
    //    NODE* tmp = cur;
    //    while (cur != nullptr) {
    //        cur = cur->next;
    //        printf(">> delete { %d, %d } \n", tmp->data.value, tmp->data.idx);
    //        delete tmp;
    //        tmp = cur;
    //    }
    //    head = nullptr;
    //}
    





    NODE* push_back(NODE* cur, const DATA&data) {

    }
    NODE* pop_back(NODE* cur) {
    }
    NODE* find_node(const DATA& data) {
        for (auto cur = head; cur != nullptr; cur = cur->next) {
            if (cur->data == data)
                return cur;
        }
        return nullptr;
    }
    NODE* find_node(NODE* cur, const DATA& data) {
        if (cur == nullptr) { return nullptr; }
        if (cur->data == data) { return cur; }
        return find_node(cur->next, data);
    }
    void remove(const DATA& data) {
        NODE* tmp = head;
        while (head != nullptr) {
            head = head->next;
            delete tmp;
            tmp = head;
        }
    }
    void clear() {
        for (auto cur = head; cur->next != nullptr; cur = cur->next) {
            NODE* tmp = cur->next;
            cur->next = tmp->next;
            printf(">> delete { %d, %d } \n", tmp->data.value, tmp->data.idx);
            delete tmp;
            cur = head;
        }
        //head = nullptr;
    }
    NODE* clear_node(NODE* cur) {
        if (cur == nullptr) return nullptr;
        cur->next = clear_node(cur->next);

        printf(">> delete { %d, %d } \n", cur->data.value, cur->data.idx);
        delete cur;
        listSize -= 1;

        return nullptr;
    }
    NODE* remove_node(NODE* cur, const DATA& data) {
        if (cur == nullptr) return nullptr;
        cur->next = remove_node(cur->next, data);

        if (cur->data == data) {
            printf(">> delete { %d, %d } \n", cur->data.value, cur->data.idx);
            delete cur;
            listSize -= 1;
        }
        return cur;
    }

    DATA& operator[](int idx) { return {}; }
    void print_inorder() {
        if (head == nullptr) { printf("empty!\n"); }
        else {
            for (auto ptr = head; ptr; ptr = ptr->next)
                ptr->data.print();
            printf("\n");
        }
    }
    void preorder(NODE* cur) {
        if (cur == nullptr) return;
        cur->data.print();
        preorder(cur->next);
    }
    void postorder(NODE* cur) {
        if (cur == nullptr) return;
        postorder(cur->next);
        cur->data.print();
    }



    //void clear() { head = clear_node(head);}
    //NODE* find(const DATA& data) { return find_node(head, data); }

    struct ITER {
        NODE* node;

        ITER(NODE* node = nullptr) { this->node = node; }
        bool operator!=(const ITER& iter) const { return node != iter.node; }
        bool operator==(const ITER& iter) const { return node == iter.node; }
        ITER& operator++() { node = node->next; return *this; }                 // ++iter
        ITER operator++(int) { ITER iter = *this; ++(*this); return iter; }     // iter++
        DATA& operator*() { return node->data; }                                // *iter
    };
    ITER begin() { return ITER(head); }
    ITER end() { return ITER(nullptr); }
};

struct DATA {
    int value, idx;

    bool operator==(const DATA& data) const {
        return (value == data.value) && (idx == data.idx);
    }
    bool operator<(const DATA& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
    void print() { printf("{ %d, %d }, ", value, idx); }
};

void test_sll() {
    SLL<DATA> sll;
    sll.clear();
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());

    sll.push_front({ 10, 1 });
    sll.push_front({ 20, 2 });
    sll.push_front({ 30, 3 });
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());

    printf("\n>> [1] pointer 이용\n");
    for (auto node = sll.head; node; node = node->next)
        printf("{ %d, %d }, ", node->data.value, node->data.idx);
    printf("\n");

    printf("\n>> [2] iterator 이용\n");
    for (auto iter = sll.begin(); iter != sll.end(); ++iter)
        printf("{ %d, %d }, ", (*iter).value, (*iter).idx);
    printf("\n");

    printf("\n>> [3] ranged-based for loop 이용\n");
    for (auto data: sll)
        printf("{ %d, %d }, ", data.value, data.idx);
    printf("\n");

    sll.clear();
    printf("empty() = %d, size() = %d\n", sll.empty(), sll.size());
}

int main() {
    //test_sll();

    SLL<DATA> sll;
    sll.clear();
    sll.push_front({ 30, 3 });
    sll.push_front({ 20, 2 });
    sll.push_front({ 10, 1 });
    sll.print_inorder();
    //sll.preorder(sll.head);     printf("\n");
    //sll.postorder(sll.head);    printf("\n");

    //sll.insert_after(sll.find_node({ 10, 1 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 20, 2 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 30, 3 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 10, 1 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 20, 2 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 30, 3 }), { 0, 0 });
    //sll.insert_after(sll.find_node({ 30, 3 })->next->next, { -1, -1 });
    //sll.print_inorder();

    //sll.head = sll.clear_node(sll.head);
    //sll.head = sll.remove_node(sll.head, { 0, 0 });
    //while (!sll.empty()) { sll.pop_front(); }
    //sll.clear();
    //sll.print_inorder();

    //sll.remove_node(sll.head, { 0, 0 });
    //sll.remove_node(sll.head, { 0, 0 });
    //sll.remove({ 0, 0 });
    //sll.print_inorder();

    //sll.head = sll.clear_node(sll.head);
    //sll.clear();
    //sll.print_inorder();

}
#endif