### [SLL] find / insert / erase / remove 구현 중

```cpp
#include <cstdio>

// Singly Linked List (head only)
template<typename TYPE>
struct SLL {
    struct NODE {
        TYPE data;
        NODE* next;

        //NODE() { data = {}; next = nullptr; }
        //NODE(const TYPE& data) { this->data; next = nullptr; }
        //NODE(const TYPE& data, NODE* node) { this->data; next = node; }
    };
    NODE* head;

    SLL() { head = nullptr; }
    void clear() { head = nullptr; }
    void push_front(const TYPE& data) {
        NODE* node = new NODE{ data, nullptr };
        if (!head) { head = node; }
        else { node->next = head; head = node; }
    }
    void pop_front() {
        if (head) {
            NODE* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    struct ITER {
        NODE* node;

        ITER() { this->node = nullptr; }
        ITER(NODE* node) { this->node = node; }
        bool operator!=(const ITER& iter) const { return this->node != iter.node; }
        bool operator==(const ITER& iter) const { return this->node == iter.node; }
        void operator++() { this->node = this->node->next; }
        TYPE& operator*() { return this->node->data; }
    };
    ITER begin() { return ITER(head); }
    ITER end() { return ITER(nullptr); }

    ITER find(const TYPE& data) {
        for (auto iter = begin(); iter != end(); ++iter)
            if (*iter == data) { return iter; }
        return end();
    }
    ITER find_before(const TYPE& data) {
        if (!head) { return end(); }
        for (auto node = head; node->next; node = node->next)
            if (node->next->data == data)
                return ITER(node);
        return end();
    }
    void insert_after(ITER iter, const TYPE& data) {
        NODE* node = new NODE{ data, nullptr };
        if (iter != end()) {
            node->next = iter.node->next;
            iter.node->next = node;
        }
    }
    void erase_after(ITER iter) {
        NODE* node = iter.node;
        if (!node) { return; }
        else if (!node->next) { return; }
        else {
            NODE* tmp = node->next;
            node->next = node->next->next;
            delete tmp;
        }
    }
    void remove(const TYPE& data) {
        ITER iter = find_before(data);
        if (iter != end()) { 
            erase_after(iter);
        }
    }
    template<typename FUNC>
    void remove_if(FUNC func) {
        for (auto iter = begin(); iter != end(); ++iter) {
            if (func(*iter)) {
                NODE* tmp = iter.node->next;
                iter.node->next = iter.node->next->next;
                delete tmp;
            }
        }
    }
};

template<typename LIST>
void print(LIST& lst) {
    printf("{ ");
    for (auto node = lst.head; node; node = node->next)
        printf("%d, ", node->data);
    printf("}\n");
}

template<typename LIST, typename ITER>
void check(LIST& lst, ITER iter, const char str[]) {
    printf(">> %s: ", str);
    if (iter == lst.begin()) { printf("iter is begin().\n"); }
    else if (iter == lst.end()) { printf("iter is end().\n"); }
    else { printf("iter's value is %d.\n", *iter); }
}

int main()
{
    SLL<int> sll;

    //printf(">> 초기화\n");
    //sll.clear();        print(sll);

    printf("\n>> 삽입\n");
    sll.push_front(4);  print(sll);
    sll.push_front(3);  print(sll);
    sll.push_front(2);  print(sll);
    sll.push_front(1);  print(sll);

    //printf("\n>> 삭제\n");
    //sll.pop_front();    print(sll);
    //sll.pop_front();    print(sll);

    //printf("\n>> 순회 [Manual for loop]\n");
    //for (auto node = sll.head; node; node = node->next)
    //    printf("%d ", node->data);

    //printf("\n>> 순회 [Range-based for loop]\n");
    //for (const auto& x: sll)
    //    printf("%d ", x);
     
    //printf("\n>> 순회 [Iterator-based for loop]\n");
    //for (auto iter = sll.begin(); iter != sll.end(); ++iter)
    //    printf("%d ", *iter);

    //auto iter = sll.begin();

    //printf("\n>> 검색 [find(x)]\n");
    //check(sll, sll.find(0), "x = 0");
    //check(sll, sll.find(1), "x = 1");
    //check(sll, sll.find(2), "x = 2");
    //check(sll, sll.find(3), "x = 3");
    //check(sll, sll.find(4), "x = 4");
    //check(sll, sll.find(5), "x = 5");

    //printf("\n>> 검색 [find_before(x)]\n");
    //check(sll, sll.find_before(0), "x = 0");
    //check(sll, sll.find_before(1), "x = 1");
    //check(sll, sll.find_before(2), "x = 2");
    //check(sll, sll.find_before(3), "x = 3");
    //check(sll, sll.find_before(4), "x = 4");
    //check(sll, sll.find_before(5), "x = 5");

    printf("\n>> 삽입\n");
    sll.insert_after(sll.find(0), 0); print(sll);
    sll.insert_after(sll.find(1), 100); print(sll);
    sll.insert_after(sll.find(2), 200); print(sll);
    sll.insert_after(sll.find(3), 300); print(sll);
    sll.insert_after(sll.find(4), 400); print(sll);
    sll.insert_after(sll.find(5), 500); print(sll);

    printf("\n>> 제거\n");
    //sll.erase_after(sll.find(0)); print(sll);
    //sll.erase_after(sll.find(1)); print(sll);
    //sll.erase_after(sll.find(2)); print(sll);
    //sll.erase_after(sll.find(3)); print(sll);
    //sll.erase_after(sll.find(4)); print(sll);
    //sll.erase_after(sll.find(5)); print(sll);

    //sll.remove(0);   print(sll);
    //sll.remove(100);   print(sll);
    //sll.remove(200);   print(sll);
    //sll.remove(300);   print(sll);
    //sll.remove(400);   print(sll);
    //sll.remove(500);   print(sll);

    //sll.remove_if([](int x) { return x > 10; });    print(sll);

    for (auto iter = sll.begin(); iter != sll.end(); ++iter)
        if (*iter > 10) {
            printf("%d\n", *iter);
            sll.remove(*iter); print(sll);
        }
    //print(sll);


    printf("\n\n>> 종료");
    return 0;
```
