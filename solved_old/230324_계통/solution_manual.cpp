#if 1
// Manual 3175 ms (WS): Array + Linked List + Queue + inline swap

//#include <vector>
//#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#define MAXL		(11) 
#define NUM_NODES	(50000)

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

template<typename Type>
struct LinkedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    void init() { head = nullptr; tail = nullptr; size = 0; }
    void push_back(const Type& data) {
        Node* node = new Node({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        size += 1;
    }
};

template<typename Type>
struct Queue{
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    void init() { head = nullptr; tail = nullptr; size = 0; }
    void push(const Type& data) {
        Node* node = new Node({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        size += 1;
    }
    void pop() {
        Node* temp = head;
        head = temp->next;
        delete temp;
        size -= 1;
    }
    Type front() { return head->data; }
    bool empty() { return size == 0; }
};

struct Species {
    int parent;
    int depth;
    LinkedList<int> childList;
};
unordered_map<string, int> speciesMap;
Species species[NUM_NODES];
int nodeCnt;

////////////////////////////////////////////////////////////////
int get_nodeIndex(char mSpecies[]) {
    int nIdx;
    auto ptr = speciesMap.find(string(mSpecies));
    if (ptr == speciesMap.end()) {
        nIdx = nodeCnt;
        speciesMap[string(mSpecies)] = nIdx;
        nodeCnt += 1;
    }
    else { nIdx = ptr->second; }
    return nIdx;
}

int get_LCA(int x, int y) {
    if (species[x].depth < species[y].depth) {
        swap(x, y);
    }
    while (species[x].depth != species[y].depth) {
        x = species[x].parent;
    }
    while (x != y) {
        x = species[x].parent;
        y = species[y].parent;
    }
    return x;
}

////////////////////////////////////////////////////////////////
void init(char mRootSpecies[MAXL])
{
    speciesMap.clear();
    for (int i = 0; i < NUM_NODES; i++) { species[i] = {}; }
    nodeCnt = 0;

    int nIdx = get_nodeIndex(mRootSpecies);
    species[nIdx].parent = -1;
}

// 50,000
void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
    int nIdx = get_nodeIndex(mSpecies);
    int pIdx = get_nodeIndex(mParentSpecies);

    species[nIdx].parent = pIdx;
    species[nIdx].depth = species[pIdx].depth + 1;

    // 그래프 인접 리스트
    species[nIdx].childList.push_back(pIdx);
    species[pIdx].childList.push_back(nIdx);
}

// 10,000 LCA
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
    int x = get_nodeIndex(mSpecies1);
    int y = get_nodeIndex(mSpecies2);
    int lca = get_LCA(x, y);

    int ret = species[x].depth + species[y].depth - species[lca].depth * 2;
    return ret;
}

// 10,000 BFS
int getCount(char mSpecies[MAXL], int mDistance)
{
    int start = get_nodeIndex(mSpecies);
    Queue<int> Q;
    int dist[NUM_NODES];
    for (int i = 0; i < nodeCnt; i++) { dist[i] = -1; }
    int ret = 0;

    dist[start] = 0;
    Q.push(start);
    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        if (dist[node] > mDistance) { break; }
        if (dist[node] == mDistance) { ret += 1; }

        for (auto ptr = species[node].childList.head; ptr; ptr=ptr->next) {
            auto next = ptr->data;
            if (dist[next] == -1) {
                dist[next] = dist[node] + 1;
                Q.push(next);
            }
        }
    }
    return ret;
}
#endif
