#if 0
// 그래프 노드 차례대로 순회 (상위 노드정보 저장 목적)
#include <vector>       // 링크드 리스트
#include <stack>        // DFS 구현
#include <queue>        // BFS 구현
using namespace std;

#define N   8           // 노드 개수

vector<int> nodes[N];   // 노드 연결정보 저장
bool visited[N];        // 노드 방문여부 저장
vector<int> path;       // 노드 방문순서 저장

void print_path(const vector<int>& path) {
    int i;
    for (i = 0; i < path.size() - 1; i++) { printf("[%d] - ", path[i]); }
    printf("[%d]\n", path[i]);
}

/////////////////////////////////////////////////////////////////////
bool dfs1(int x, int target) {
    if (!visited[x]) {
        visited[x] = 1;
        path.push_back(x);

        if (x == target) {
            printf("Found the target!\n");
            return true;
        }
        for (int next : nodes[x])
            if (dfs1(next, target) == true) { return true; }
    }
    return false;
}

bool dfs2(int start, int target) {
    stack<int> S;
    S.push(start);

    while (!S.empty()) {
        int x = S.top(); S.pop();

        if (!visited[x]) {
            visited[x] = 1;
            path.push_back(x);

            if (x == target) {
                printf("Found the target!\n");
                return true;
            }
            for (int next : nodes[x])
                S.push(next);
        }
    }
    return false;
}

bool dfs3(int x, int target) {
    if (x == target) {
        printf("Found the target!\n");
        return true;
    }
    for (int nx : nodes[x])
        if (!visited[nx]) {
            visited[nx] = true;
            path.push_back(nx);
            if (dfs3(nx, target) == true) { return true; }
        }
    return false;
}

bool bfs(int start, int target) {
    queue<int> Q;
    visited[start] = true;
    path.push_back(start);
    Q.push(start);

    while (!Q.empty()) {
        int x = Q.front(); Q.pop();

        if (x == target) {
            printf(">> Found the target!\n");
            return true;   
        }
        for (int nx : nodes[x])
            if (!visited[nx]) {
                visited[nx] = true;
                path.push_back(nx);
                Q.push(nx);
            }
    }
    return false;
}


/////////////////////////////////////////////////////////////////////
void init() {
    for (int i = 0; i < N; i++) {
        nodes[i].clear();   // 노드 연결정보 초기화
        visited[i] = 0;     // 노드 방문정보 초기화
    }
    path.clear();           // 노드 방문순서 초기화

    nodes[0] = { 1, 2 };
    nodes[1] = { 0, 2, 4, 7 };
    nodes[2] = { 0, 1, 3 };
    nodes[3] = { 2, 5 };
    nodes[4] = { 1, 6 };
    nodes[5] = { 3 };
    nodes[6] = { 4 };
    nodes[7] = { 1 };
}

int main() 
{
    init();
    dfs1(0, 4);
    print_path(path);   // [0] - [1] - [2] - [3] - [5] - [4]

    init();
    dfs2(0, 4);
    print_path(path);   // [0] - [2] - [3] - [5] - [1] - [7] - [4]

    init();
    visited[0] = true;
    path.push_back(0);
    dfs3(0, 4);
    print_path(path);   // [0] - [1] - [2] - [3] - [5] - [4]

    init();
    bfs(0, 4);
    print_path(path);   // [0] - [1] - [2] - [4] - [7] - [3]

    return 0;
}
#endif