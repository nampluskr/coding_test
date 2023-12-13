#if 1
// ��� ��� ã��
#include <vector>
#include <queue>
#include "maze.h"
using namespace std;

int maxDist, minDist;

// ���� Ž��
void dfs(int row, int col, int goalR, int goalC, int dist = 1) {
	if (row == goalR && col == goalC) {
		if (dist > maxDist) {	// ���� ���
			maxDist = dist;
			display(visited);
			printf(">> Found a solution! (Max. dist = %d)\n", maxDist);
		}
		return;
	}
	for (int k = 0; k < 4; k++) {
		int nr = row + dr[k], nc = col + dc[k];

		if (0 <= nr && nr < N && 0 <= nc && nc < M)
			if (!visited[nr][nc] && map[nr][nc] == 0 && dist > 3) {
				visited[nr][nc] = visited[row][col] + 1;
				dfs(nr, nc, goalR, goalC, dist + 1);
				visited[nr][nc] = 0;
			}
	}
}

// ���� ġ��
//void dfs(int row, int col, int goalR, int goalC, int dist = 1) {
//	if (row == goalR && col == goalC) {
//		maxDist = dist;
//		display(visited);
//		printf(">> Found a solution! (Max. dist = %d)\n", maxDist);
//		return;
//	}
//	for (int k = 0; k < 4; k++) {
//		int nr = row + dr[k], nc = col + dc[k];
//
//		if (0 <= nr && nr < N && 0 <= nc && nc < M)
//			if (!visited[nr][nc] && map[nr][nc] == 0 && dist >= maxDist) {
//				visited[nr][nc] = visited[row][col] + 1;
//				dfs(nr, nc, goalR, goalC, dist + 1);
//				visited[nr][nc] = 0;
//			}
//	}
//}

// �ִ� ���
void bfs(int startR, int startC, int goalR, int goalC) {
	queue<Data> Q;
	visited[startR][startC] = 1;
	Q.push({ startR, startC, visited });

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int row = cur.pos.row, col = cur.pos.col;
		auto& visited = cur.visited;

		if (row == goalR && col == goalC) {
			display(visited);
			continue;
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
}


int main()
{
	Position start = { 0, 5 };
	Position goal = { 6, 6 };

	init();
	visited[start.row][start.col] = 1;
	maxDist = 0;
	dfs(start.row, start.col, goal.row, goal.col);

	//init();
	//bfs(start.row, start.col, goal.row, goal.col);

	return 0;

}
#endif