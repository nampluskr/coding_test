#if 0
// 경로가 존재 유/무 반환 (찾으면 종료, 못 찾으면 전부 탐색)
#include <vector>
#include <queue>
#include "maze.h"
using namespace std;

// 최단 경로 아님 (전체 경로 중 특정 경로 하나)
bool dfs(int row, int col, int goalR, int goalC) {
	if (row == goalR && col == goalC) {
		printf(">> Found a solution!\n");
		display(visited);
		return true;
	}
	for (int k = 0; k < 4; k++) {
		int nr = row + dr[k], nc = col + dc[k];

		if (0 <= nr && nr < N && 0 <= nc && nc < M)
			if (!visited[nr][nc] && map[nr][nc] == 0) {
				visited[nr][nc] = visited[row][col] + 1;
				if (dfs(nr, nc, goalR, goalC) == true) { return true; }
				visited[nr][nc] = 0;
			}
	}
	return true;
}

// 최단 경로
bool bfs(int startR, int startC, int goalR, int goalC) {
	queue<Data> Q;
	visited[startR][startC] = 1;
	Q.push({ startR, startC, visited });

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int row = cur.pos.row, col = cur.pos.col;
		auto& visited = cur.visited;

		if (row == goalR && col == goalC) {
			printf(">> Found a solution!\n");
			display(visited);
			return true;
		}
		for (int k = 0; k < 4; k++) {
			int nr = row + dr[k], nc = col + dc[k];

			if (0 <= nr && nr < N && 0 <= nc && nc < M)
				if (!visited[nr][nc] && map[nr][nc] == 0) {
					visited[nr][nc] = visited[row][col] + 1;
					Q.push({ nr, nc, visited });
					visited[nr][nc] = 0;
				}
		}
	}
	return false;
}


int main()
{
	Position start = { 0, 5 };
	Position goal = { 6, 6 };

	init();
	visited[start.row][start.col] = 1;
	dfs(start.row, start.col, goal.row, goal.col);

	init();
	bfs(start.row, start.col, goal.row, goal.col);

	return 0;

}
#endif