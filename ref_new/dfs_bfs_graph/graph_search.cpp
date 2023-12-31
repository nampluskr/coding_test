﻿#if 0
// 그래프 검색 (찾으면 방문 종료)
#include "graph.h"

/////////////////////////////////////////////////////////////////////

bool dfs1(int x, int target) {
    if (!visited[x]) {
        visited[x] = true; history.push_back(x);

        if (x == target) { return true; }   // Found the target!

        for (int next : nodes[x].nodeList)
            if (!visited[next]) {
                parent[next] = x;
                if (dfs1(next, target) == true) return true;
            }
    }
    return false;
}

void dfs2(int x0, int target) {
    stack<int> S;
    S.push(x0);

    while (!S.empty()) {
        int x = S.top(); S.pop();

        if (!visited[x]) {
            visited[x] = true; history.push_back(x);

            if (x == target) { return; }   // Found the target!

            for (int next : nodes[x].nodeList)
                if (!visited[next]) {
                    parent[next] = x;
                    S.push(next);
                }
        }
    }
}


bool dfs3(int x, int target) {
    if (x == target) { return true; }   // Found the target!

    for (int next : nodes[x].nodeList)
        if (!visited[next]) {
            visited[next] = true; history.push_back(next);
            parent[next] = x;
            if (dfs3(next, target) == true) { return true; }
        }
    return false;
}


void bfs(int x0, int target) {
    queue<int> Q;
    visited[x0] = true; history.push_back(x0);
    Q.push(x0);

    while (!Q.empty()) {
        int x = Q.front(); Q.pop();

        for (int next : nodes[x].nodeList)
            if (!visited[next]) {
                visited[next] = true; history.push_back(next);
                parent[next] = x;

                if (next == target) { return; }   // Found the target!
                Q.push(next);
            }
    }
}

int main()
{
    set_graph();
    int start = get_nodeIndex("A");
    int target = get_nodeIndex("G");

    printf("\n[Type-1] DFS\n");
    init();
    dfs1(start, target); print_list(history);   // [A]-[B]-[D]-[E]-[F]-[C]-[G]
    trace(start, target); print_list(path);     // [A]-[C]-[G]

    printf("\n[Type-2] DFS\n");
    init();
    dfs2(start, target); print_list(history);   // [A]-[C]-[I]-[J]-[H]-[G]
    trace(start, target); print_list(path);     // [A]-[C]-[G]

    printf("\n[Type-3] DFS\n");
    init();
    visited[start] = true; history.push_back(start);
    dfs3(start, target); print_list(history);   // [A]-[B]-[D]-[E]-[F]-[C]-[G]
    trace(start, target); print_list(path);     // [A]-[C]-[G]

    printf("\n[Type-4] DFS\n");
    init();
    bfs(start, target); print_list(history);    // [A]-[B]-[C]-[D]-[G]
    trace(start, target); print_list(path);     // [A]-[C]-[G]

    return 0;
}
#endif