#if 0
// 그래프 순회 (모든 노드 방문)
#include "graph.h"

void dfs1(int x) {
    if (!visited[x]) {
        visited[x] = true; history.push_back(x);

        for (int next : nodes[x].nodeList)
            if (!visited[next]) {
                parent[next] = x;
                dfs1(next);
            }
    }
}

void dfs2(int x0) {
    stack<int> S;
    S.push(x0);

    while (!S.empty()) {
        int x = S.top(); S.pop();

        if (!visited[x]) {
            visited[x] = true; history.push_back(x);

            for (int next : nodes[x].nodeList)
                if (!visited[next]) {
                    parent[next] = x;
                    S.push(next);
                }
        }
    }
}


void dfs3(int x) {

    for (int next : nodes[x].nodeList)
        if (!visited[next]) {
            visited[next] = true; history.push_back(next);
            parent[next] = x;
            dfs3(next);
        }
}


void bfs(int x0) {
    queue<int> Q;
    visited[x0] = true; history.push_back(x0);
    Q.push(x0);

    while (!Q.empty()) {
        int x = Q.front(); Q.pop();

        for (int next: nodes[x].nodeList)
            if (!visited[next]) {
                visited[next] = true; history.push_back(next);
                parent[next] = x;
                Q.push(next);
            }
    }
}

int main()
{
    set_graph();
    int start = get_nodeIndex("A");
    int end = get_nodeIndex("J");

    printf("\n[Type-1] DFS\n");
    init();
    dfs1(start); print_list(history);    // [A]-[B]-[D]-[E]-[F]-[C]-[G]-[H]-[I]-[J]
    trace(start, end); print_list(path); // [A]-[C]-[I]-[J]

    printf("\n[Type-2] DFS\n");
    init();
    dfs2(start); print_list(history);    // [A]-[C]-[I]-[J]-[H]-[G]-[B]-[D]-[F]-[E]
    trace(start, end); print_list(path); // [A]-[C]-[I]-[J]

    printf("\n[Type-3] DFS\n");
    init();
    visited[start] = true; history.push_back(start);
    dfs3(start); print_list(history);    // [A]-[B]-[D]-[E]-[F]-[C]-[G]-[H]-[I]-[J]
    trace(start, end); print_list(path); // [A]-[C]-[I]-[J]

    printf("\n[Type-4] DFS\n");
    init();
    bfs(start); print_list(history);     // [A]-[B]-[C]-[D]-[G]-[H]-[I]-[E]-[F]-[J]
    trace(start, end); print_list(path); // [A]-[C]-[I]-[J]

    return 0;
}
#endif