#if 0
// 그래프 출발점에서 목적지 노드까지 경로가 있는지 탐색 (Backtracking, Decision Problem)
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


// 최단 경로를 찾지는 않음
bool dfs(int x, int target) {
    if (x == target) {
        printf(">> Found the target!\n");
        //print_path(path);
        return true;
    }
    for (int nx : nodes[x]) {
        if (!visited[nx]) {
            visited[nx] = true;     // global
            path.push_back(nx);     // global

            if (dfs(nx, target) == true) { return true; }

            visited[nx] = false;    // backtrack
            path.pop_back();        // backtrack
        }
    }
    return false;
}

struct Info {
    int x;
    bool visited[N];
    vector<int> path;

    Info(int x, const bool visited[], const vector<int>& path) {
        this->x = x;
        for (int i = 0; i < N; i++) { this->visited[i] = visited[i]; }
        this->path.clear();
        for (int x : path) { this->path.push_back(x); }
    }
};

// 최단 경로를 찾음
Info bfs(int start, int target) {
    queue<Info> Q;
    visited[start] = true;              // global
    path.push_back(start);              // global
    Q.push({ start, visited, path });   // deep copy

    Info ret = Q.front();
    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        int x = cur.x;
        auto& visited = cur.visited;
        auto& path = cur.path;

        if (x == target) {
            printf(">> Found the target!\n");
            //print_path(path);
            ret = cur; break;
            //return cur;   
        }
        for (int nx : nodes[x]) {
            if (!visited[nx]) {
                visited[nx] = true;             // local
                path.push_back(nx);             // local
                Q.push({ nx, visited, path });  // deep copy
                visited[nx] = false;            // backtrack
                path.pop_back();                // backtrack
            }
        }
    }
    return ret;
}

void init() {
    for (int i = 0; i < N; i++) {
        nodes[i].clear();   // 노드 연결정보 초기화
        visited[i] = false; // 노드 방문정보 초기화
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
    int start = 0, target = 5;

    init();
    visited[start] = true;
    path.push_back(start);
    if (dfs(start, target) == true) { printf(">> Solution exist!\n"); }
    else { printf(">> Solution does not exist!"); }
    print_path(path);

    init();
    auto ret = bfs(start, target);
    if (ret.x != start) { printf(">> Solution exist!\n"); }
    else { printf(">> Solution does not exist!"); }
    print_path(ret.path);

    return 0;
}

#endif