#if 1
// STL 1058 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdio.h>

#define NUM_NODES   (12000 + 1)
#define NUM_DAYS    (1000000 + 1)

struct Node {
    char name[11];
    int parent;
    int depth;
};
Node nodes[NUM_NODES];
int nodeCnt;

//////////////////////////////////////////////////////////////////////////////
#define MAX_TABLE   70077
#define MAX_HEAP    NUM_NODES*10

unsigned long hashfunc(const char* str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

struct ListNode {
    int idx;
    ListNode* next;
};

ListNode heap[MAX_HEAP];
int hrp;
ListNode* hashTable[MAX_TABLE];

ListNode* appendListNode(int idx, ListNode* oldHead) {
    ListNode* newNode = &heap[hrp++];
    newNode->idx = idx;
    newNode->next = oldHead;
    return newNode;
}


//////////////////////////////////////////////////////////////////////////////
int get_nodeIndex(const char mName[]) {
    int hashkey = hashfunc(mName);

    ListNode* current = hashTable[hashkey];
    while (current != 0) {
        if (strcmp(mName, nodes[current->idx].name) == 0)
            return current->idx;
        current = current->next;
    }

    return -1;
}

//////////////////////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    for (int i = 0; i < NUM_NODES; i++) { nodes[i] = {}; }
    nodeCnt = 0;

    //for (int i = 0; i < MAX_HEAP; i++) { heap[i] = { 0, nullptr }; }
    //hrp = 0;

    int nIdx = nodeCnt;
    int hashkey = hashfunc(mAncestor);
    hashTable[hashkey] = appendListNode(nodeCnt, hashTable[hashkey]);
    nodeCnt += 1;

    strcpy(nodes[nIdx].name, mAncestor);
    nodes[nIdx].parent = -1;
    nodes[nIdx].depth = 0;

    //printf(">> hrp = %d\n", hrp);
}

int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int nIdx = get_nodeIndex(mName);
    if (nIdx == -1) {
        nIdx = nodeCnt;
        int hashkey = hashfunc(mName);
        hashTable[hashkey] = appendListNode(nodeCnt, hashTable[hashkey]);
        nodeCnt += 1;
    }
    int pIdx = get_nodeIndex(mParent);

    strcpy(nodes[nIdx].name, mName);
    nodes[nIdx].parent = pIdx;
    nodes[nIdx].depth = nodes[pIdx].depth + 1;

    return nodes[nIdx].depth;
}

int distance(char mName1[], char mName2[])
{
    return 0;
}

int count(int mDay)
{
    return 0;
}
#endif