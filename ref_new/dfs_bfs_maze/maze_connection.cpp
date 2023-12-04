#if 1
#include <vector>
#include <queue>
#include "maze.h"
using namespace std;


void dfs(int x, int y, int xn, int yn) {
	if (x == xn && y == yn) {
		display(visited);
		return;
	}
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k], ny = y + dy[k];

		if (0 <= nx && nx < N && 0 <= ny && ny < M)
			if (!visited[nx][ny] && map[nx][ny] == 0) {
				visited[nx][ny] = visited[x][y] + 1;
				dfs(nx, ny, xn, yn);
				visited[nx][ny] = 0;
			}
	}
}



int main()
{
	int x0 = 0, y0 = 5;		// start
	int xn = 6, yn = 6;		// goal

	init(x0, y0);
	dfs(x0, y0, xn, yn);

    return 0;

}
#endif