#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define N 8         // number of nodes

vector<int> nodes[N];
int visited[N];
int parent[N];
vector<int> path;


// stack과 동일 구조
void dfs1(int x) {
    if (!visited[x]) {      // 생략가능
        visited[x] = 1;     // global
        path.push_back(x);  // global

        for (int next : nodes[x])
            if (!visited[next]) {
                parent[next] = x;
                dfs1(next);
            }
    }
}

// queue와 동일 구조
void dfs2(int x) {

    for (int next : nodes[x])
        if (!visited[next]) {
            visited[next] = 1;      // global
            path.push_back(next);   // global
            parent[next] = x;       // global
            dfs2(next);
        }
}

void dfs3(int x) {
    stack<int> S;
    S.push(x);

    while (!S.empty()) {
        int cur = S.top(); S.pop();

        if (!visited[cur]) {        // 생략가능
            visited[cur] = 1;
            path.push_back(cur);
            for (int next : nodes[cur]) {
                if (!visited[next]) {
                    parent[next] = cur;
                    S.push(next);
                }
            }
        }
    }
}

void trace(const int parent[], int start, int end) {
    stack<int> S;
    for (int x = end; x != start; x = parent[x]) { S.push(x); }
    S.push(start);

    while (!S.empty()) {
        int x = S.top(); S.pop();
        printf("%d ", x);
    }
    printf("\n");
}

void init() {
    for (int i = 0; i < N; i++) { 
        nodes[i].clear();
        visited[i] = 0;
        parent[i] = -1;
    }
    path.clear();

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
    //init();
    //dfs1(0);
    //trace(parent, 0, 5);
    //trace(parent, 0, 7);

    //init();
    //visited[0] = 1;
    //path.push_back(0);
    //dfs2(0);
    //trace(parent, 0, 5);
    //trace(parent, 0, 7);

    init();
    dfs3(0);
    trace(parent, 0, 5);
    trace(parent, 0, 7);

    return 0;
}