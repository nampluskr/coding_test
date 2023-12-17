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

    //LinkedList<Type>() { clear(); }
    ListNode* new_node(const Type& data) {
        ListNode* node = new ListNode;
        node->data = data;
        node->next = nullptr;
        return node;
    }
    void clear() { head = tail = nullptr; listSize = 0; }
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
    LinkedList<MapNode>* table[max_table];
    int mapSize;

    MapNode* new_node(const Key& key, const Value& value) {
        MapNode* node = new MapNode;
        node->key = key;
        node->value = value;
        return node;
    }
    int hashfunc(const Key& key) { return key % max_table; }
    void clear() { 
        for (int i = 0; i < max_table; i++) table[i].clear();
        mapSize = 0;
    }
    void emplace(const Key& key, const Value& value) {
        int hash = hashfunc(key);
        table[hash].push_back(new_node(key, value));
        mapSize++;
    }
    MapNode* find(const Key& key) {
        int hash = hashfunc(key);
        for (auto node = table[hash].head; node; node = node->next)
            if (node->data.key == key)
                return node->data.value;
        return nullptr;
    }
    Value& operator[](const Key& key) {
        MapNode* node = find(key);
        if (node == nullptr) {
            int hash = hashfunc(key);
            table[hash]->push_back(new_node(key, {}));
            mapSize++;
            return table[hash].tail->data.value;
        }
        return node->value;
    }
};

void test_intMap() {
    HashMap<int, int, 3> intMap;
    intMap.clear();
    
    intMap.emplace(10, 100);
    //intMap.emplace(20, 200);
    //intMap.emplace(30, 300);
    
    intMap[10] = 200;
    intMap[10] = 300;
    //intMap[30] = 300;
}

void test_listMap() {
    HashMap<int, LinkedList<int>, 3> listMap;
    listMap.clear();

    listMap.emplace(10, {});
    //listMap.emplace(20, {});
    //listMap.emplace(30, {});

    listMap[10].push_back(100);
    listMap[10].push_back(200);
    listMap[10].push_back(300);

}

int main()
{
    //test_intMap();

    test_listMap();

    return 0;
}
#endif