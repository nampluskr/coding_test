#if 0
// 그래프 검색 (깊이 지정)
#include "graph.h"


void dfs1(int x, int depth) {
    if (!visited[x]) {
        visited[x] = true; history.push_back(x);

        for (int next : nodes[x].nodeList)
            if (!visited[next] && depth > 0) {
                parent[next] = x;
                dfs1(next, depth - 1);
            }
    }
}

void dfs2(int x0, int depth) {
    struct Data { int x, depth; };
    stack<Data> S;
    S.push({ x0, depth });

    while (!S.empty()) {
        auto cur = S.top(); S.pop();

        if (!visited[cur.x]) {
            visited[cur.x] = true; history.push_back(cur.x);

            for (int next : nodes[cur.x].nodeList)
                if (!visited[next] && cur.depth > 0) {
                    parent[next] = cur.x;
                    S.push({ next, cur.depth - 1 });
                }
        }
    }
}

void dfs3(int x, int depth) {

    for (int next: nodes[x].nodeList)
        if (!visited[next] && depth > 0) {
            visited[next] = true; history.push_back(next);
            parent[next] = x;
            dfs3(next, depth - 1);
        }
}

void bfs(int x0, int depth) {
    struct Data { int x, depth; };
    queue<Data> Q;
    visited[x0] = true; history.push_back(x0);
    Q.push({ x0, depth });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        for (int next : nodes[cur.x].nodeList)
            if (!visited[next] && cur.depth > 0) {
                visited[next] = true; history.push_back(next);
                parent[next] = cur.x;
                Q.push({ next, cur.depth - 1 });
            }
    }
}

int main()
{
    set_graph();
    int start = get_nodeIndex("A");
    int depth = 2;

    printf("\n[Type-1] DFS\n");
    init();
    dfs1(start, depth); print_list(history);   // [A]-[B]-[D]-[C]-[G]-[H]-[I]

    printf("\n[Type-2] DFS\n");
    init();
    dfs2(start, depth); print_list(history);   // [A]-[C]-[I]-[H]-[G]-[B]-[D]

    printf("\n[Type-3] DFS\n");
    init();
    visited[start] = true; history.push_back(start);
    dfs3(start, depth); print_list(history);   // [A]-[B]-[D]-[C]-[G]-[H]-[I]

    printf("\n[Type-4] DFS\n");
    init();
    bfs(start, depth); print_list(history);   // [A]-[B]-[C]-[D]-[G]-[H]-[I]
}

#endif