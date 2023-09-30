#if 1
// Manual 845 ms / STL 1135 ms
//#ifndef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#endif

#include <string.h>

#define NUM_NODES   (12000 + 1)
#define NUM_DAYS    (1000000 + 1)

struct Node {
    int parent;
    int depth;
    int first_day;
    int last_day;
};
Node nodes[NUM_NODES];
int nodeCnt;

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

#define MAX_TABLE   70007
struct HashMap {
    struct Data {
        char key[11];
        int value;
        Data() { strcpy(this->key, ""); this->value = 0; }
        Data(const char key[], int value) { strcpy(this->key, key); this->value = value; }
    };
    LinkedList<Data> table[MAX_TABLE];
    
    unsigned long hash(const char str[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) { 
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++)
            table[i].clear();
    }
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
    int find(const char key[]) {
        int hashkey = hash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (strcmp(node->data.key, key) == 0)
                return node->data.value;
        }
        return -1;
    }
};

HashMap nodeMap;

//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(const char mName[]) {
    int nIdx;
    auto ptr = nodeMap.find(mName);
    if (ptr == -1) {
        nIdx = nodeCnt;
        nodeMap.emplace(mName, nIdx);
        nodeCnt += 1;
    }
    else { nIdx = ptr; }
    return nIdx;
}

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

int get_lca(int x, int y) {
    if (nodes[x].depth < nodes[y].depth) { swap(x, y); }

    while (nodes[x].depth != nodes[y].depth) {
        x = nodes[x].parent;
    }
    while (x != y) {
        x = nodes[x].parent;
        y = nodes[y].parent;
    }
    return x;
}

#define NUM_VALUES  1000001
#define BUCKET_SIZE 1000
#define NUM_BUCKETS 1001

struct Partition {
    int buckets[NUM_BUCKETS];
    int values[NUM_VALUES];
    int N;      // bucket size

    void init() {
        N = BUCKET_SIZE;
        for (int i = 0; i < NUM_BUCKETS; i++) buckets[i] = {};
        for (int i = 0; i < NUM_VALUES; i++) values[i] = {};
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { values[i] += value; }
            return;
        }
        while (left / N == s) { values[left++] += value; }
        while (right / N == e) { values[right--] += value; }
        for (int i = s + 1; i <= e - 1; i++) { buckets[i] += value; }
    }
    int query(int idx) {
        int ret = buckets[idx / N] + values[idx];
        return ret;
    }
};
Partition part;

//////////////////////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    for (int i = 0; i < NUM_NODES; i++) { nodes[i] = {}; }
    nodeCnt = 0;
    nodeMap.clear();

    int nIdx = get_nodeIndex(mAncestor);
    nodes[nIdx] = { -1, 0, 0, mLastday };

    part.init();
    part.update(0, mLastday, 1);
}

int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int nIdx = get_nodeIndex(mName);
    int pIdx = get_nodeIndex(mParent);

    nodes[nIdx].parent = pIdx;
    nodes[nIdx].depth = nodes[pIdx].depth + 1;
    nodes[nIdx].first_day = mFirstday;
    nodes[nIdx].last_day = mLastday;

    part.update(mFirstday, mLastday, 1);

    return nodes[nIdx].depth;
}

int distance(char mName1[], char mName2[])
{
    int x = get_nodeIndex(mName1);
    int y = get_nodeIndex(mName2);

    int lca = get_lca(x, y);
    int ret = nodes[x].depth + nodes[y].depth - 2 * nodes[lca].depth;
    return ret;
}

int count(int mDay)
{
    int ret = part.query(mDay);
    return ret;
}
#endif
