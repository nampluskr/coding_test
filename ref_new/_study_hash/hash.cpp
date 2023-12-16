#if 1
#include <cstdio>

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;
    int listSize;

    ListNode* new_node(const Type& data) {
        ListNode* node = new ListNode;
        node->data = data;
        node->next = nullptr;
        return node;
    }

    void clear() { head = tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new_node(data);
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        listSize++;
    }
};

template<typename Key, typename Value, int max_table>
struct HashMap {
    struct MapNode {
        Key key;
        Value value;
    };
    LinkedList<MapNode> table[max_table];

    int hashfunc(const Key& key) { return key % max_table; }
    void clear() { for (int i = 0; i < max_table; i++) table[i].clear(); }
    void emplace(const Key& key, const Value& value) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, value });
    }
    MapNode* find(const Key& key) {
        int hash = hashfunc(key);
        // node: ListNode, node->data: MapNode
        for (auto node = table[hash].head; node; node = node->next)
            if (node->data.key == key)
                return &node->data;
        return nullptr;
    }
    Value& operator[](const Key& key) {
        auto node = find(key);
        if (node == nullptr) {
            int hash = hashfunc(key);
            table[hash].push_back({});
            return table[hash].head->data.value;
        }
        return node->value;
    }
};


struct Data {
    int value1, value2;
    //Data() { this->key = 0; this->value = 0; }
    //Data(int key, int value) { this->key = key; this->value = value; }
};

int main()
{
    LinkedList<int> intList;
    intList.clear();
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);

    //LinkedList<Data> dataList;
    //dataList.clear();
    //dataList.push_back({ 10, 1});
    //dataList.push_back({ 20, 2 });
    //dataList.push_back({ 30, 3 });

    //HashMap<int, int, 3> intMap;
    //intMap.clear();
    //intMap.emplace(10, 1);
    //intMap.emplace(20, 2);
    //intMap.emplace(30, 3);
    //intMap.find(10);
    //auto x = intMap[30];
    //auto y = intMap[50];

    HashMap<int, LinkedList<int>, 3> listMap;
    listMap.clear();
    listMap.emplace(10, intList);
    listMap[10].push_back(2);
    listMap[10].push_back(3);
    listMap[10].push_back(4);




    //HashMap<int, Data, 3> dataMap;
    //dataMap.clear();
    //dataMap.emplace(40, { 400, 4 } );
    //dataMap.emplace(50, { 500, 5 });
    //dataMap.emplace(60, { 600, 6 });


    return 0;
}
#endif