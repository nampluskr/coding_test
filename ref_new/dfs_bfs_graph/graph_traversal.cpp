#if 0
// 그래프 노드 차례대로 순회 (상위 노드정보 저장 목적)
#include <vector>       // 링크드 리스트
#include <stack>        // DFS 구현
#include <queue>        // BFS 구현
using namespace std;

#define N   8           // 노드 개수

vector<int> nodes[N];   // 노드 연결정보 저장
bool visited[N];        // 노드 방문여부 저장
int parent[N];          // 상위 노드정보 저장
vector<int> history;    // 노드 방문순서 저장
vector<int> path;       // 최단거리 경로 저장

// 이웃 노드 방문 순서 (작은 노드 번호부터)
// [0] - [1] - [2] - [3] - [5] - [4] - [6] - [7]
void dfs1(int x) {
    if (!visited[x]) {
        visited[x] = true;
        history.push_back(x);

        for (int next : nodes[x]) {
            if (!visited[next]) {   // parent 구할 때 필요
                parent[next] = x;   // 아니면 생략 가능
                dfs1(next);
            }
        }
    }
}

// 이웃 노드 방문 순서 (큰 노드 번호부터)
// [0] - [2] - [3] - [5] - [1] - [7] - [4] - [6]
void dfs2(int x0) {
    stack<int> S;
    S.push(x0);

    while (!S.empty()) {
        int x = S.top(); S.pop();

        if (!visited[x]) {
            visited[x] = true;
            history.push_back(x);
            for (int next : nodes[x]) {
                if (!visited[next]) {   // parent 구할 때 필요
                    parent[next] = x;   // 아니면 생략 가능
                    S.push(next);
                }
            }
        }
    }
}


// queue와 동일 구조 (global 변수 사전 초기화 필요)
// [0] - [1] - [2] - [3] - [5] - [4] - [6] - [7]
void dfs3(int x) {

    // global 변수 visited, history 시작 노드 정보 반영 필수
    for (int next : nodes[x])
        if (!visited[next]) {
            visited[next] = true;
            history.push_back(next);
            parent[next] = x;
            dfs3(next);
        }
}

// 이웃 노드 방문 순서 (작은 노드 번호부터)
// [0] - [1] - [2] - [4] - [7] - [3] - [6] - [5]
void bfs(int x0) {
    queue<int> Q;
    visited[x0] = 1;
    history.push_back(x0);
    Q.push(x0);

    while (!Q.empty()) {
        int x = Q.front(); Q.pop();

        for (int next : nodes[x])
            if (!visited[next]) {
                visited[next] = true;
                history.push_back(next);
                parent[next] = x;
                Q.push(next);
            }
    }
}

void trace(const int parent[], int start, int end) {
    if (end == start) { path.push_back(end); }
    if (parent[end] == -1) { return; }
    trace(parent, start, parent[end]);
    path.push_back(end);
}

void show(const vector<int>& vec) {
    int i;
    for (i = 0; i < vec.size() - 1; i++) { printf("[%d] - ", vec[i]); }
    printf("[%d]\n", vec[i]);
}

void init() {
    for (int i = 0; i < N; i++) {
        nodes[i].clear();   // 노드 연결정보 초기화
        visited[i] = false; // 노드 방문정보 초기화
        parent[i] = -1;     // 상위 노드정보 초기화
    }
    history.clear();        // 노드 방문순서 초기화
    path.clear();           // 최단거리 경로 초기화

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
    dfs1(0);
    show(history);
    trace(parent, 0, 4);
    show(path);

    init();
    dfs2(0);
    show(history);
    trace(parent, 0, 4);
    show(path);

    init();
    visited[0] = 1;
    history.push_back(0);
    dfs3(0);
    show(history);
    trace(parent, 0, 4);
    show(path);

    init();
    bfs(0);
    show(history);
    trace(parent, 0, 4);
    show(path);

    return 0;
}
#endif
