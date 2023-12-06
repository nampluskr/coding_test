#include <vector>
#include <queue>
using namespace std;

#define MAX_N           350
#define MAX_CHARGERS    200
#define INF             0x7fffffff

int(*map)[MAX_N];
int dist[MAX_N][MAX_N]; // dijkstra
int N;                  // map size
int range;

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

struct Data {
    int mID, dist;
    bool operator<(const Data& data) const { return this->dist > data.dist; }
};

struct Charger {
    int row, col;
    vector<Data> chargerList;
};
Charger chargers[MAX_CHARGERS];

struct Position {
    int row, col;
};
queue<Position> Q; 
priority_queue<Data> PQ;

/////////////////////////////////////////////////////////////////////
void chargerBFS(int row, int col) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) { dist[i][j] = INF; }
    dist[row][col] = 0;

    while (!Q.empty()) { Q.pop(); }
    Q.push({ row, col });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();

        if (dist[cur.row][cur.col] >= range) break;

        for (int k = 0; k < 4; k++) {
            int nr = cur.row + dr[k];
            int nc = cur.col + dr[k];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (dist[nr][nc] != INF) continue;
            if (map[nr][nc] == 1) continue;

            dist[nr][nc] = dist[cur.row][cur.col] + 1;
            Q.push({ nr, nc });
        }
    }
}
/////////////////////////////////////////////////////////////////////
void init(int _N, int mRange, int mMap[MAX_N][MAX_N])
{
    N = _N;
    range = mRange;
    map = mMap;
    for (int i = 0; i < MAX_CHARGERS; i++) { chargers[i] = {}; }

}

//mID는 TC 내에서 0에서 시작해 설치 시 마다 1씩 증가한다.
void add(int mID, int mRow, int mCol)
{
    chargers[mID] = { mRow, mCol };
    chargerBFS(mRow, mCol);

    for (int i = 0; i < mID; i++) {
        int row = chargers[i].row;
        int col = chargers[i].col;

        if (dist[row][col] <= range) {
            chargers[i].chargerList.push_back({ mID, dist[row][col] });
            chargers[mID].chargerList.push_back({ i, dist[row][col] });
        }
    }

}

int distance(int mFrom, int mTo)
{

    return 0;
}