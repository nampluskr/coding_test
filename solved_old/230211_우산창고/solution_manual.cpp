#if 1
// Manual 95 ms (WS): Array + Linked List + Priority Queue + inline min/swap
//#include <vector>
//#include <queue>
//using namespace std;

#define NUM_NODES   10000

inline int min(int a, int b) { return (a < b) ? a : b; }
inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

template<typename Type>
struct LinkedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(const Type& data) {
        Node* node = new Node({data, nullptr});
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};
struct Data {
    int x;
    int dist;

    bool operator<(const Data& data) const {
        return (dist > data.dist) || (dist == data.dist && x > data.x);
    }
};
struct Node {
    int mID;
    int parent;                 // 부모 노드
    int depth;                  // 루트로부터 누적 깊이
    int distance;               // 루트로부터 누적 거리

    int quantity;               // 우산 개수
    int total;                  // 자기 + 하위 노드 누적 개수
    LinkedList<Data> childList; // 인접 리스트: {연결 노드, 거리}

    void update_quantity(int mQuantity) {
        quantity += mQuantity;
        total += mQuantity;
    }
};
Node nodes[NUM_NODES];
int nodeCnt;

#if 0
template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue {
    Type heap[NUM_NODES];
    int heapSize = 0;

    void init() { heapSize = 0; }
    void push(const Type& data) {
        heap[heapSize] = data;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            Type temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int current = 0;

        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current]) {
                break;
            }
            Type temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
};
#endif

//////////////////////////////////////////////////////////////////////////////
int get_LCA(int x, int y) {
    if (nodes[x].depth < nodes[y].depth)
        swap(x, y);

    while (nodes[x].depth != nodes[y].depth) {
        x = nodes[x].parent;
    }
    while (x != y) {
        x = nodes[x].parent;
        y = nodes[y].parent;
    }
    return x;
}

void update_parents(int mIdx, int quantity) {
    int pIdx = nodes[mIdx].parent;
    while (pIdx != -1) {
        nodes[pIdx].total += quantity;
        pIdx = nodes[pIdx].parent;
    }
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mParent[], int mDistance[], int mQuantity[])
{
    nodeCnt = N;
    for (int i = 0; i < N; i++) { nodes[i] = {}; }

    nodes[0].mID = 0;
    nodes[0].parent = mParent[0];
    nodes[0].update_quantity(mQuantity[0]);

    for (int i = 1; i < N; i++) {
        nodes[i].mID = i;
        nodes[i].parent = mParent[i];
        nodes[i].depth = nodes[mParent[i]].depth + 1;
        nodes[i].distance = nodes[mParent[i]].distance + mDistance[i];

        nodes[i].update_quantity(mQuantity[i]);
        update_parents(i, mQuantity[i]);

        // 그래프 인접 리스트
        nodes[i].childList.push_back({ mParent[i], mDistance[i] });
        nodes[mParent[i]].childList.push_back({ i, mDistance[i] });
    }
}

int carry(int mFrom, int mTo, int mQuantity)
{
    nodes[mFrom].update_quantity(-mQuantity);
    update_parents(mFrom, -mQuantity);

    nodes[mTo].update_quantity(mQuantity);
    update_parents(mTo, mQuantity);

    int lca = get_LCA(mFrom, mTo);
    int distance = nodes[mFrom].distance + nodes[mTo].distance - nodes[lca].distance * 2;
    int ret = distance * mQuantity;
    return ret;
}

int gather(int mID, int mQuantity)
{
    PriorityQueue<Data> Q;
    bool visited[NUM_NODES];
    for (int i = 0; i < nodeCnt; i++) { visited[i] = false; }
    int ret = 0;

    visited[mID] = true;
    Q.push({ mID, 0 });
    while (!Q.empty() && mQuantity > 0) {
        auto node = Q.top(); Q.pop();

        if (node.x != mID) {
            int quantity = min(mQuantity, nodes[node.x].quantity);
            ret += carry(node.x, mID, quantity);
            mQuantity -= quantity;
        }
        for (auto ptr = nodes[node.x].childList.head; ptr; ptr=ptr->next) {
            const auto& next = ptr->data;
            if (!visited[next.x]) {
                visited[next.x] = true;
                int lca = get_LCA(next.x, mID);
                int dist = nodes[next.x].distance + nodes[mID].distance - nodes[lca].distance * 2;
                Q.push({ next.x, dist });
            }
        }
    }
    return ret;
}

int sum(int mID)
{
    int ret = nodes[mID].total;
    return ret;
}
#endif
