#if 1
#include <cstdio>

template<typename Type>
struct ListNode {
    Type data;
    ListNode* next;
};

template<typename Type>
struct LinkedList {
    ListNode<Type>* head;
    ListNode<Type>* tail;
    int listSize;

    ListNode<Type>* new_node(const Type& data) {
        ListNode<Type>* node = new ListNode<Type>;
        node->data = data;
        node->next = nullptr;
        return node;
    }
    void clear() { head = tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode<Type>* node = new_node(data);
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        listSize++;
    }
    void push_front(const Type& data) {
        ListNode<Type>* node = new_node(data);
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        listSize++;
    }
    void pop_front() {
        ListNode<Type>* node = head;
        head = node->next;
        delete node;
        listSize--;
        if (empty()) { clear(); }
    }
    bool empty() { return listSize == 0; }    // head == nullptr
    Type front() { return head->data; } 
    Type back() { return tail->data; }
    int size() { return listSize; }
    ListNode<Type>* find(const Type& data) {
        for (auto node = head; node; node = node->next)
            if (node->data == data)
                return node;
        return nullptr;
    }
};

template<typename Type>
struct Queue : LinkedList<Type> {
    void push(const Type& data) { this->push_front(data); }
    void pop() { this->pop_front(); }
};

template<typename Type>
struct Stack : LinkedList<Type> {
    void push(const Type& data) { this->push_back(data); }
    void pop() { this->pop_front(); }
    Type top() { return this->front(); }
};

template<typename Type>
void print(LinkedList<Type>& list) {
    if (list.empty()) {
        printf(">> (empty = %d, size = %d) head = NULL, tail = NULL \n", 
            list.empty(), list.size()); 
        return;
    }
    printf(">> (empty = %d, size = %d) head = %d, tail = %d\n",
        list.empty(), list.size(), list.front(), list.back());
    auto node = list.head;
    for (; node->next; node = node->next) {
        printf("[%d] - ", node->data);
    }
    printf("[%d]\n", node->data);
}

/////////////////////////////////////////////////////////////////////

void test_list() {
    LinkedList<int> L;
    L.clear();
    print(L);

    L.push_back(30);
    L.push_back(40);
    print(L);

    L.push_front(20);
    L.push_front(10);
    print(L);

    printf("find(10): %d\n", L.find(10) ? 1 : -1);
    printf("find(50): %d\n", L.find(50) ? 1 : -1);

    L.pop_front();
    print(L);

    while (!L.empty()) { L.pop_front(); }
    print(L);
}

void test_stack() {
    Stack<int> S;
    S.clear();
    print(S);

    S.push(10);
    S.push(20);
    S.push(30);
    print(S);

    S.pop();
    print(S);
}

void test_queue() {
    Queue<int> Q;
    Q.clear();
    print(Q);

    Q.push(10);
    Q.push(20);
    Q.push(30);
    print(Q);

    Q.pop();
    print(Q);
}


int main()
{
    printf("\nTest list:\n");
    test_list();

    printf("\nTest stack:\n");
    test_stack();

    printf("\nTest queue:\n");
    test_queue();

    return 0;
}
#endif