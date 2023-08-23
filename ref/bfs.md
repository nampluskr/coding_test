### [BFS] 230819 박테리아 번식

```cpp
#include <vector>
#include <queue>
#include <math.h>
#include <tuple>
using namespace std;

#define N   10

int grid[N][N];
int visited[N][N];

int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

//int dx[12] = { -2, -1, -1, -1,  0,  0, 0, 0,  1, 1, 1, 2 };
//int dy[12] = {  0, -1,  0,  1, -2, -1, 1, 2, -1, 0, 1, 0 };

struct Data {
    int row;
    int col;
    int dist;

    bool operator<(const Data& data) const {
        /*if (dist > data.dist) { return true; }
        else if (dist == data.dist && row > data.row) { return true; }
        else if (dist == data.dist && row == data.row && col > data.col) { return true; }
        else { return false; }*/

        return make_tuple(dist, row, col) > make_tuple(data.dist, data.row, data.col);
        //return make_tuple(row, col, dist) > make_tuple(data.row, data.col, data.dist);
    }
};

void bfs(int x0, int y0, int size) {
    //queue<Data> Q;
    priority_queue<Data> Q;

    int cnt = 1;
    grid[x0][y0] = cnt;
    visited[x0][y0] = cnt;
    Q.push({ x0, y0, 0 });
    while (!Q.empty()) {
        auto node = Q.top(); Q.pop();
        int x = node.row, y = node.col;

        if (cnt == size) { break; }

        for (int k = 0; k < 12; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >=0 && nx < N && ny >= 0 && ny < N)
                if (visited[nx][ny] == 0 && cnt < size) {
                    int dist = abs(nx - x0) + abs(ny - y0);
                    cnt += 1;
                    grid[nx][ny] = cnt;
                    visited[nx][ny] = visited[x][y] + 1;
                    Q.push({ nx, ny, dist });
                }
        }
    }
}

void print(int grid[N][N]) {
    for (int i = 0; i < N * 3; i++) {
        printf("=");
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
}

void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }
}

int main()
{
    init();
    //print(grid);

    bfs(2, 7, 11);
    print(grid);

}
```
