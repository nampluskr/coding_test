#if 1
// Manusl 314 ms (WS): Array + LinkedList + inline min/max
//#include <vector>
#include <unordered_map>
using namespace std;

#define NUM_NODES   (17000 + 1000)
#define NUM_GROPUS  1000
#define DELETED     1

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

template<typename Type>
struct LinckedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(const Type& data) {
        Node* node = new Node({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Node {
    int mId;
    int num;
    int parent;
    int state;

    int num_children;
    LinckedList<int> childList;
};
unordered_map<int, int> nodeMap;
Node nodes[NUM_NODES];
int nodeCnt;

int groups[NUM_GROPUS];
int groupCnt;

//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(int mId) {
    int nIdx;
    auto ptr = nodeMap.find(mId);
    if (ptr == nodeMap.end()) {
        nIdx = nodeCnt;
        nodeMap[mId] = nIdx;
        nodeCnt += 1;
    }
    else {
        nIdx = ptr->second;
        if (nodes[nIdx].state == DELETED) { nIdx = -1; }
    }
    return nIdx;
}
void update_parents(int nIdx, int num) {
    int pIdx = nodes[nIdx].parent;
    while (pIdx != -1) {
        nodes[pIdx].num += num;
        pIdx = nodes[pIdx].parent;
    }
}
void remove_children(int nIdx) {
    nodes[nIdx].state = DELETED;
    for (auto ptr = nodes[nIdx].childList.head; ptr; ptr = ptr->next) {
        int child = ptr->data;
        if (nodes[child].state != DELETED)
            remove_children(child);
    }
}
//////////////////////////////////////////////////////////////////////////////
void init(int N, int mId[], int mNum[])
{
    nodeMap.clear();
    for (int i = 0; i < NUM_NODES; i++) { nodes[i] = {}; }
    nodeCnt = 0;

    for (int i = 0; i < NUM_GROPUS; i++) { groups[i] = {}; }
    groupCnt = N;

    for (int i = 0; i < N; i++) {
        int nIdx = get_nodeIndex(mId[i]);
        nodes[nIdx].mId = mId[i];
        nodes[nIdx].num = mNum[i];
        nodes[nIdx].parent = -1;
    }
}

// 17,000
int add(int mId, int mNum, int mParent)
{
    int ret = -1;
    int nIdx = get_nodeIndex(mId);
    int pIdx = get_nodeIndex(mParent);

    if (nodes[pIdx].num_children < 3) {
        nodes[pIdx].num_children += 1;
        nodes[pIdx].childList.push_back(nIdx);

        nodes[nIdx].mId = mId;
        nodes[nIdx].num = mNum;
        nodes[nIdx].parent = pIdx;

        update_parents(nIdx, mNum);
        ret = nodes[pIdx].num;
    }
    else { nodes[nIdx].state = DELETED; }
    return ret;
}

// 2,000
int remove(int mId)
{
    int ret = -1;
    int nIdx = get_nodeIndex(mId);

    if (nIdx != -1) {
        remove_children(nIdx);
        update_parents(nIdx, -nodes[nIdx].num);
        nodes[nodes[nIdx].parent].num_children -= 1;
        ret = nodes[nIdx].num;
    }
    return ret;
}

// 1,000
int distribute(int K)
{
    int ret;
    int start = 0;
    int end = 0;
    for (int i = 0; i < groupCnt; i++) {
        groups[i] = nodes[i].num;
        end = max(end, groups[i]);
    }
    // Parametric search
    while (start <= end) {
        int mid = start + (end - start) / 2;
        int sum = 0;
        for (int i = 0; i < groupCnt; i++) { sum += min(mid, groups[i]); }

        if (sum <= K) {
            ret = mid;
            start = mid + 1;
        }
        else { end = mid - 1; }
    }
    return ret;
}
#endif
