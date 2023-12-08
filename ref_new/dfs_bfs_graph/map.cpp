#if 0
#include <vector>
#include <queue>
using namespace std;

#define N   5

int map[N][N];
int dist[N][N];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };


void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            map[i][j] = 0;
            dist[i][j] = 0;
        }
}

void show_map(const int a[N][N]) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", a[i][j]);
        printf("\n");
    }
}

int get_dist(int row1, int col1, int row2, int col2) {
    return abs(row1 - row2) + abs(col1 - col2);
}

struct Position {
    int row, col, depth, dist;
    int to(int row, int col) { return abs(this->row - row) + abs(this->col - col); }
};
queue<Position> Q;

void bfs(int row, int col, int count) {
    init();

    dist[row][col] = 1;
    Position start = { row, col, 1, 0 };
    Q.push(start);

    int cnt = -1;
    int depth = -1;

    while (!Q.empty()) {
        Position cur = Q.front(); Q.pop();

        // 특정 깊이 도달 여부
        if (cur.depth == depth) {
            printf(">> cnt = %d (count = %d)\n", cnt, count);
            break;
        }

        for (int k = 0; k < 4; k++) {
            Position next = { cur.row + dr[k], cur.col + dc[k] };

            if (next.row < 0 || next.row >= N || next.col < 0 || next.col >= N) continue;
            if (dist[next.row][next.col] != 0) continue;

            // 새노드 방문 처리
            cnt++;
            dist[next.row][next.col] = dist[cur.row][cur.col] + 1;
            if (cnt == count) { depth = cur.depth + 1; }    // 특정 노드 도달 여부

            // 다음 방문할 노드 저장
            Q.push({ next.row, next.col, cur.depth + 1, start.to(next.row, next.col )});

        }
    }
}

int cnt;
void dfs(int r, int c, int depth) {
    if (depth == 3) { 
        show_map(dist);
        return;
    }
     
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];

        if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
        if (dist[nr][nc] != 0) continue;

        cnt++;
        dist[nr][nc] = dist[r][c] + 1;
        dfs(nr, nc, depth + 1);
        dist[nr][nc] = 0;
    }
}

int main()
{
    bfs(2, 2, 2);
    show_map(dist);

    //init();
    //cnt = 0;
    //dist[0][0] = 1;
    //dfs(0, 0, 0);
    ////show_map(dist);
    //printf("%d\n", cnt);

    return 0;
}
#endif
