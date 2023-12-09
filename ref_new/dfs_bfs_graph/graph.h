#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>           // 링크드 리스트  history, path
#include <stack>            // DFS 구현
#include <queue>            // BFS 구현
#include <string>           // 노드 이름 문자열
#include <unordered_map>    // 노드 이름 Mapping (문자열 -> 정수)
using namespace std;

#define N           10      // 노드 개수
#define MAX_NAME    11      // 노드 이름 길이

struct Node {
    char name[MAX_NAME];
    vector<int> nodeList;
};

Node nodes[N];          // 노드 연결정보 저장 (링크드 리스트)
bool visited[N];        // 노드 방문여부 저장
int parent[N];          // 상위 노드정보 저장 (parent[root] = -1)

int nodeCnt;
unordered_map<string, int> nodeMap;

vector<int> history;    // 방문 노드순서 저장 (링크드 리스트)
vector<int> path;       // 최단거리 경로 저장 (링크드 리스트)


/////////////////////////////////////////////////////////////////////
int get_nodeIndex(const char name[]) {
    int nIdx;
    auto ptr = nodeMap.find(name);
    if (ptr == nodeMap.end()) {
        nIdx = nodeCnt++;
        strcpy(nodes[nIdx].name, name);
        nodeMap.emplace(name, nIdx);
    }
    else { nIdx = ptr->second; }
    return nIdx;
}

void add(const char name1[], const char name2[]) {
    int nIdx1 = get_nodeIndex(name1);
    int nIdx2 = get_nodeIndex(name2);
    nodes[nIdx1].nodeList.push_back(nIdx2);
    nodes[nIdx2].nodeList.push_back(nIdx1);
}

void print_list(const vector<int>& list) {
    int i;
    for (i = 0; i < list.size() - 1; i++)
        printf("[%s]-", nodes[list[i]].name);
    printf("[%s]\n", nodes[list[i]].name);
}

void trace(int start, int end) {
    if (end == start) { path.push_back(end); }
    if (parent[end] == -1) { return; }
    trace(start, parent[end]);
    path.push_back(end);
}

void set_graph() {
    for (int i = 0; i < N; i++) { nodes[i] = {}; }
    nodeCnt = 0;
    nodeMap.clear();

    add("A", "B"); add("A", "C");
    add("B", "D");
    add("C", "G"); add("C", "H"); add("C", "I");
    add("D", "E"); add("D", "F");
    add("I", "J");
}

void init() {
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    history.clear();
    path.clear();
}
