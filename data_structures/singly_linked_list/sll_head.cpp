#if 1
#include <cstdio>

template<typename TYPE>
struct SLL {
    struct NODE {
        TYPE data;
        NODE* next;
    };
    NODE* head;

    void clear() { head = nullptr; }
    void push_front(const TYPE& data) {
        NODE* node = new NODE{ data, nullptr };
        if (!head) { head = node; }
        else { node->next = head; head = node; }
    }
    void pop_front() {
        NODE* tmp = head;
        head = head->next;
        delete tmp;
    }

    struct ITER {
        NODE* node;

        ITER(NODE* node = nullptr) { this->node = node; }
        bool operator!=(const ITER& iter) const { return this->node != iter.node; }
        bool operator==(const ITER& iter) const { return this->node == iter.node; }
        ITER& operator++() { this->node = this->node->next; return *this; }    // ++iter
        TYPE& operator*() { return this->node->data; }          // *iter
    };

    ITER begin() { return ITER(head); }
    ITER end() { return ITER(nullptr); }
    ITER find(const TYPE& data) {
        //for (auto iter = begin(); iter != end(); ++iter)
        //    if (*iter == data)
        //        return iter;
        for (auto node = head; node; node = node->next)
            if (node->data == data)
                return ITER(node);
        return end();
    }
    ITER find_before(const TYPE& data) {
        //if (!head) { return end(); }
        for (auto node = head; node->next; node = node->next)
            if (node->next->data == data)
                return ITER(node);
        return end();
    }
    ITER find(ITER iter, const TYPE& data) {
        if (iter == end()) { return end(); }
        else if (*iter == data) { return iter; }
        else { return find(++iter, data); }
    }
    void insert_after(ITER iter, const TYPE& data) {
        NODE* node = new NODE{ data, nullptr };
        if (iter != end()) {
            node->next = iter.node->next;
            iter.node->next = node;
            //iter = ITER(node);
        }
        //else { push_front(data); iter = begin(); }
    }
    void erase_after(ITER iter) {
        NODE* node = iter.node;
        if (!node) { return; }
        else if (!node->next) { return; }
        else {
            NODE* tmp = node->next;
            node->next = tmp->next;
            delete tmp;
        }
    }
    void remove(const TYPE& data) {
        //ITER iter = find_before(data);
        //if (iter != end())
        //    erase_after(iter);
       
        for (auto node = head; node->next; node = node->next) {
            if (node->data == data) { pop_front(); node = head; }
            if (node->next->data == data) {
                erase_after(ITER(node));
                //NODE* tmp = node->next;
                //node->next = tmp->next;
                //delete tmp;
                node = head;
            }
        }
    }
    template<typename FUNC>
    void remove_if(FUNC func) {
        for (auto node = head; node->next; node = node->next) {
            if (func(node->data)) { pop_front(); node = head; }
            if (func(node->next->data)) {
                erase_after(ITER(node));
                //NODE* tmp = node->next;
                //node->next = tmp->next;
                //delete tmp;
                node = head;
            }
        }
    }
};

template<typename LIST>
void print(LIST& lst) {
    printf(">> { ");
    //for (auto node = lst.head; node; node = node->next)
    //    printf("%d, ", node->data);
    //for (auto x : lst)
    //    printf("%d, ", x);
    for (auto iter = lst.begin(); iter != lst.end(); ++iter)
        printf("%d, ", *iter);

    printf("}\n");
}

template<typename LIST, typename ITER>
void check(LIST& lst, ITER iter, const char str[]) {
    printf("%s: ", str);
    if (iter == lst.end()) { printf("iter is end().\n"); }
    else if (iter == lst.begin()) { printf("iter is begin() and its value is %d\n", *iter); }
    else { printf("iter's value is %d.\n", *iter); }
}


int main()
{
    SLL<int> sll;
    sll.clear();

    printf("\n[삽입] - push_front()\n");
    sll.push_front(3);  print(sll);
    sll.push_front(2);  print(sll);
    sll.push_front(1);  print(sll);

    //printf("\n[제거] - pop_front()\n");
    //sll.pop_front();    print(sll);
    //sll.pop_front();    print(sll);
    //sll.pop_front();    print(sll);

    //printf("\n[검색] - find()\n");
    //check(sll, sll.find(0), "find(0)");
    //check(sll, sll.find(1), "find(1)");
    //check(sll, sll.find(2), "find(2)");
    //check(sll, sll.find(3), "find(3)");
    //check(sll, sll.find(4), "find(4)");

    //printf("\n[검색] - find_before()\n");
    //check(sll, sll.find_before(0), "find_before(0)");
    //check(sll, sll.find_before(1), "find_before(1)");
    //check(sll, sll.find_before(2), "find_before(2)");
    //check(sll, sll.find_before(3), "find_before(3)");
    //check(sll, sll.find_before(4), "find_before(4)");


    printf("\n[삽입] - insert_after()\n");
    sll.insert_after(sll.find(0), 0);   print(sll);
    sll.insert_after(sll.find(1), 100); print(sll);
    sll.insert_after(sll.find(2), 200); print(sll);
    sll.insert_after(sll.find(3), 300); print(sll);
    sll.insert_after(sll.find(4), 400); print(sll);

    //printf("\n[삭제] - eraser_after()\n");
    //sll.erase_after(sll.find(0));   print(sll);
    //sll.erase_after(sll.find(1));   print(sll);
    //sll.erase_after(sll.find(2));   print(sll);
    //sll.erase_after(sll.find(3));   print(sll);
    //sll.erase_after(sll.find(4));   print(sll);

    printf("\n[삭제] - remove()\n");
    sll.remove(0);   print(sll);
    sll.remove(1);   print(sll);
    sll.remove(100);   print(sll);
    sll.remove(200);   print(sll);
    sll.remove(300);   print(sll);
    sll.remove(400);   print(sll);

    //printf("\n[삭제] - remove_if()\n");
    //sll.remove_if([](int x) { return x > 10; });   print(sll);


    return 0;
}
#endif