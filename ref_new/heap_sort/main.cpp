#include "heapsort.h"

#define MAX_DATA    10
#define ADDED   0
#define REMOVED 1

struct Data {
    int value, idx, state;
    bool operator<(const Data& data) const { return value < data.value; }
};
Data dataList[MAX_DATA];
int addCnt;
int removeCnt;
IntMapInt dataMap;

Data dataSorted[MAX_DATA];
Data topk[MAX_DATA];


void heapsort() {
    PriorityQueue<Data> Q; Q.clear();
    for (int i = 0; i < addCnt; i++) {
        if (dataList[i].state != REMOVED) { Q.push(dataList[i]); }
    }

    int cnt = 0;
    while (!Q.empty()) {
        dataSorted[cnt++] = Q.top(); Q.pop();
    }
}

void get_topk(int k) {
    PriorityQueue<Data> Q; Q.clear();
    for (int i = 0; i < addCnt; i++) {
        if (dataList[i].state != REMOVED) { Q.push(dataList[i]); }
    }

    int cnt = 0;
    while (!Q.empty() && cnt < k) {
        topk[cnt++] = Q.top(); Q.pop();
    }
}


int get_dataIndex(int ID) {
    int idx;
    auto ret = dataMap.find(ID);
    if (ret == -1) {
        idx = addCnt++;
        dataMap.emplace(ID, idx);
    }
    else { idx = ret; }
    return idx;
}

////////////////////////////////////////////////////////////////////
void init() {
    for (int i = 0; i < MAX_DATA; i++) { 
        dataList[i] = {};
        dataSorted[i] = {};
        topk[i] = {};
    }
    addCnt = 0;
    removeCnt = 0;
}

void add(int ID, int value) {
    int idx = get_dataIndex(ID);
    if (dataList[idx].state == REMOVED) {
        dataList[idx].state = ADDED;
        removeCnt--;
    }
    dataList[idx] = { value, idx, ADDED };

    printf("(size = %d) ID = %d is added.\n", addCnt - removeCnt, ID);
}

void remove(int ID) {
    int idx = get_dataIndex(ID);
    if (dataList[idx].state == ADDED) {
        dataList[idx].state = REMOVED;
        removeCnt++;

        printf("(size = %d) ID = %d is removed.\n", addCnt - removeCnt, ID);
    }
}

int main() 
{
    init();

    add(222, 100);
    add(111, 200);
    add(444, 300);
    add(333, 400);
    add(555, 500);

    remove(333);
    remove(444);

    add(333, 400);
    remove(444);

    heapsort();
    get_topk(2);

    return 0;
}