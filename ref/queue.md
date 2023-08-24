## [STL] Queue

```cpp
#include <queue>
using namespace std;

struct Data {
    int value1;
    int value2;
};

queue<Data> Q;

int main()
{
    // 초기화
    while (!Q.empty()) { Q.pop(); }

    // 입력
    Q.push({ 3, 30 });
    Q.push({ 2, 20 });
    Q.push({ 1, 10 });

    // 크기
    int size = Q.size();
    printf("%d\n", size);

    // 탐색
    while (!Q.empty()) {
        auto data = Q.front(); Q.pop();

        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```

## [Manual] Queue

```cpp
#include <stdio.h>

template<typename Type>
struct Queue {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int listSize = 0;

    void clear() { head = nullptr; tail = nullptr; listSize = 0; }
    void push(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr});
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        listSize += 1;
    }
    void pop() {
        ListNode* node = head;
        head = node->next;
        delete node;
        listSize -= 1;
    }
    Type front() { return head->data; }
    bool empty() { return listSize == 0; }
    int size() { return listSize; }
};

struct Data {
    int value1;
    int value2;
};

Queue<Data> Q;

int main()
{
    // 초기화
    while (!Q.empty()) { Q.pop(); }

    // 입력
    Q.push({ 3, 30 });
    Q.push({ 2, 20 });
    Q.push({ 1, 10 });

    // 크기
    int size = Q.size();
    printf("%d\n", size);

    // 탐색
    while (!Q.empty()) {
        auto data = Q.front(); Q.pop();

        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```