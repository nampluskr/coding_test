## [STL] Linked List 

```cpp
#include <vector>
using namespace std;

struct Data {
    int value1;
    int value2;
};

vector<Data> dataList;

int main()
{
    // 초기화
    dataList.clear();

    // 입력
    dataList.push_back({ 3, 30 });
    dataList.push_back({ 2, 20 });
    dataList.push_back({ 1, 10 });

    // 크기
    int size = dataList.size();
    printf("%d\n", size);

    // 탐색
    for (auto data : dataList) {
        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```

## [Manual] Linked List 

```cpp
#include <stdio.h>

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int listSize = 0;

    void clear() { head = nullptr; tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        listSize += 1;
    }
    int size() { return listSize; }
};

struct Data {
    int value1;
    int value2;
};

LinkedList<Data> dataList;

int main()
{
    // 초기화
    dataList.clear();

    // 입력
    dataList.push_back({ 3, 30 });
    dataList.push_back({ 2, 20 });
    dataList.push_back({ 1, 10 });

    // 크기
    int size = dataList.size();
    printf("%d\n", size);

    // 탐색
    for (auto node = dataList.head; node; node = node->next){
        auto data = node->data;
        printf("%d, %d\n", data.value1, data.value2);
    }

    return 0;
}
```