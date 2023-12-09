#if 1
// 그래프 순회 (방문한 노드 개수 반환)
#include "graph.h"

int dfs1(int x, int cnt = 1) {
    if (!visited[x]) {
        visited[x] = true; history.push_back(x);

        for (int next : nodes[x].nodeList)
            if (!visited[next]) {
                parent[next] = x;
                cnt = dfs1(next, cnt + 1);
            }
    }
    return cnt;
}

int dfs2(int x0) {
    stack<int> S;
    S.push(x0);
    int cnt = 1;

    while (!S.empty()) {
        int x = S.top(); S.pop();

        if (!visited[x]) {
            visited[x] = true; history.push_back(x);

            for (int next : nodes[x].nodeList)
                if (!visited[next]) {
                    cnt++;
                    parent[next] = x;
                    S.push(next);
                }
        }
    }
    return cnt;
}


int dfs3(int x, int cnt = 1) {

    for (int next : nodes[x].nodeList)
        if (!visited[next]) {
            visited[next] = true; history.push_back(next);
            parent[next] = x;
            cnt = dfs3(next, cnt + 1);
        }
    return cnt;
}


int bfs(int x0) {
    queue<int> Q;
    visited[x0] = true; history.push_back(x0);
    Q.push(x0);
    int cnt = 1;

    while (!Q.empty()) {
        int x = Q.front(); Q.pop();

        for (int next : nodes[x].nodeList)
            if (!visited[next]) {
                cnt++;
                visited[next] = true; history.push_back(next);
                parent[next] = x;
                Q.push(next);
            }
    }
    return cnt;
}

int main()
{
    set_graph();
    int start = get_nodeIndex("A");

    printf("\n[Type-1] DFS\n");
    init();
    printf(">> cnt = %d\n", dfs1(start));
    print_list(history);   // [A]-[B]-[D]-[E]-[F]-[C]-[G]-[H]-[I]-[J]

    printf("\n[Type-2] DFS\n");
    init();
    printf(">> cnt = %d\n", dfs2(start));
    print_list(history);   // [A]-[C]-[I]-[J]-[H]-[G]-[B]-[D]-[F]-[E]

    printf("\n[Type-3] DFS\n");
    init();
    visited[start] = true; history.push_back(start);
    printf(">> cnt = %d\n", dfs3(start));
    print_list(history);   // [A]-[B]-[D]-[E]-[F]-[C]-[G]-[H]-[I]-[J]

    printf("\n[Type-4] BFS\n");
    init();
    printf(">> cnt = %d\n", bfs(start));
    print_list(history);   // [A]-[B]-[C]-[D]-[G]-[H]-[I]-[E]-[F]-[J]

    return 0;
}
#endif