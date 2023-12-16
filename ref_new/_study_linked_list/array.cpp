#if 0
#include <cstdio>

template<typename Type, int max_size>
struct List {
    Type list[max_size * 2];
    int head, tail, listSize;

    void clear() { head = tail = max_size - 1; listSize = 0; }
    void push_back(const Type& data) {
        if (empty()) { head++; }
        list[++tail] = data;
        listSize++;
    }
    void push_front(const Type& data) {
        if (empty()) { tail--; }
        list[--head] = data;
        listSize++;
    }
    void pop_back() {
        tail--; listSize--;
        if (empty()) { clear(); }
    }
    void pop_front() {
        head++; listSize--;
        if (empty()) { clear(); }
    }
    bool empty() { return listSize == 0; }  // head == max_size - 1
    Type front() { return list[head]; }
    Type back() { return list[tail]; }
    int size() { return listSize; }
    int find(const Type& data) {
        for (int i = head; i <= tail; i++)
            if (list[i] == data)
                return i;
        return -1;
    }
};

template<typename Type, int max_size>
struct Stack {
    Type list[max_size];
    int head, tail, listSize;

    void clear() { head = tail = -1; listSize = 0; }
    void push(const Type& data) {
        if (empty()) { head++; }
        list[++tail] = data;
        listSize++;
    }
    void pop() { 
        tail--; listSize--;
        if (empty()) { clear(); }
    }
    bool empty() { return listSize == 0; }  // head == - 1
    Type top() { return list[tail]; }
    int size() { return listSize; }
};


template<typename Type, int max_size>
struct Queue {
    Type list[max_size];
    int head, tail, listSize;

    void clear() { head = tail = -1; listSize = 0; }
    void push(const Type& data) {
        if (empty()) { head++; }
        list[++tail] = data;
        listSize++;
    }
    void pop() {
        head++; listSize--;
        if (empty()) { clear(); }
    }
    bool empty() { return listSize == 0; }  // head == - 1
    Type front() { return list[tail]; }
    int size() { return listSize; }
};

template<typename Type>
void print(Type& X) {
    printf(">> (empty = %d, size = %d) head = %d, tail = %d\n",
        X.empty(), X.size(), X.head, X.tail);
    if (!X.empty()) {
        int i = X.head;
        for (; i < X.tail; i++) { printf("[%d] - ", X.list[i]); }
        printf("[%d]\n", X.list[i]);
    }
}

void test_list() {
    List<int, 5> L;
    L.clear();
    print(L);

    L.push_back(10);
    L.push_back(20);
    print(L);

    printf("find(10): %d\n", L.find(10));
    printf("find(30): %d\n", L.find(30));

    L.pop_back();
    L.pop_back();
    print(L);

    L.push_front(100);
    L.push_front(200);
    print(L);

    L.pop_front();
    L.pop_front();
    print(L);

}

void test_stack() {
    Stack<int, 5> S;
    S.clear();
    print(S);

    S.push(10);
    S.push(20);
    S.push(30);
    print(S);

    S.pop();
    S.pop();
    S.pop();
    print(S);

    S.push(100);
    print(S);
}

void test_queue() {
    Queue<int, 5> Q;
    Q.clear();
    print(Q);

    Q.push(10);
    Q.push(20);
    Q.push(30);
    print(Q);

    Q.pop();
    Q.pop();
    Q.pop();
    print(Q);

    Q.push(100);
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
