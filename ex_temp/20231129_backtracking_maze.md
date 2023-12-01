### x, y 대신 Position 객체를 이용해 작성해 볼 것! (그래프에 일반화 하여 적용 가능)

### [Backtracking] Show visited 2D array

```cpp
#include <vector>
#include <queue>
using namespace std;

#define N 7
#define M 11

int map[N][M] = {
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
};

struct Position {
	int x, y;
};

int visited[N][M];		// global

struct Data{
	Position pos;
	int visited[N][M];	// deep copied
	int dist;

	// for queue<Position>
	Data(int x, int y, const int visited[N][M]) {
		this->pos.x = x, this->pos.y = y;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				this->visited[i][j] = visited[i][j];
		this->dist = 0;
	}
	// for priority_queue<Position>
	Data(int x, int y, const int visited[N][M], int dist) {
		this->pos.x = x, this->pos.y = y;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				this->visited[i][j] = visited[i][j];
		this->dist = dist;
	}
	bool operator<(const Data& data) const { return this->dist > data.dist; }
};

int dx[] = { -1, 0, 1,  0 };
int dy[] = {  0, 1, 0, -1 };


/////////////////////////////////////////////////////////////////////
void init(int x0, int y0) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
	visited[x0][y0] = 1;
}

void display(const int map[N][M]) {
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) { printf("%2d ", map[i][j]); }
		printf("\n");
	}
}

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


void bfs(int x0, int y0, int xn, int yn) {
	queue<Data> Q;
	Q.push({ x0, y0, visited });	// visited[x0][y0] = 1;

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int x = cur.pos.x, y = cur.pos.y;

		if (x == xn && y == yn) {
			display(cur.visited);
			continue;
		}
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k], ny = y + dy[k];

			if (0 <= nx && nx < N && 0 <= ny && ny < M)
				if (!cur.visited[nx][ny] && map[nx][ny] == 0) {
					cur.visited[nx][ny] = cur.visited[x][y] + 1;
					Q.push({ nx, ny, cur.visited });
					cur.visited[nx][ny] = 0;
				}
		}
	}
}


int cal_dist(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void best_first_search(int x0, int y0, int xn, int yn) {
	priority_queue<Data> Q;
	Q.push({ x0, y0, visited, cal_dist(x0, y0, xn, yn) });

	while (!Q.empty()) {
		auto cur = Q.top(); Q.pop();
		int x = cur.pos.x, y = cur.pos.y;

		if (x == xn && y == yn) {
			display(cur.visited);
			continue;
		}
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k], ny = y + dy[k];

			if (0 <= nx && nx < N && 0 <= ny && ny < M)
				if (!cur.visited[nx][ny] && map[nx][ny] == 0) {
					cur.visited[nx][ny] = cur.visited[x][y] + 1;
					Q.push({ nx, ny, cur.visited, cal_dist(nx, ny, xn, yn) });
					cur.visited[nx][ny] = 0;
				}
		}
	}
}


int main()
{
	int x0 = 0, y0 = 5;		// start
	int xn = 6, yn = 6;		// goal
	
	printf("\n>> DFS\n");
	init(x0, y0);
	dfs(x0, y0, xn, yn);
	
	printf("\n>> BFS\n");
	init(x0, y0);
	bfs(x0, y0, xn, yn);

	printf("\n>> Best First Search\n");
	init(x0, y0);
	best_first_search(x0, y0, xn, yn);

	return 0;
}
```

### [Backtracking] Show visited 2D array & path of positions (x, y)

```cpp
#include <vector>
#include <queue>
using namespace std;

#define N 7
#define M 11

int map[N][M] = {
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
};

struct Position {
	int x, y;
};

int visited[N][M];				// global
vector<Position> path;			// global

struct Data {
	Position pos;
	int visited[N][M];			// deep copied!!!
	vector<Position> path;		// deep copied!!!
	int dist;

	// for queue<Position> with deep copy
	Data(int x, int y, const int visited[N][M], const vector<Position>& path) {
		this->pos.x = x, this->pos.y = y;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				this->visited[i][j] = visited[i][j];
		for (auto pos : path) { this->path.push_back(pos); }
		this->dist = 0;
	}
	// for priority_queue<Position> with deep copy
	Data(int x, int y, const int visited[N][M], const vector<Position>& path, int dist) {
		this->pos.x = x, this->pos.y = y;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				this->visited[i][j] = visited[i][j];
		for (auto pos : path) { this->path.push_back(pos); }
		this->dist = dist;
	}
	bool operator<(const Data& data) const { return this->dist > data.dist; }
};

int dx[] = { -1, 0, 1,  0 };
int dy[] = { 0, 1, 0, -1 };


/////////////////////////////////////////////////////////////////////
void init(int x0, int y0) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
	visited[x0][y0] = 1;
	path.push_back({ x0, y0 });
}

void display(const int map[N][M]) {
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) { printf("%2d ", map[i][j]); }
		printf("\n");
	}
}

void show_path(const vector<Position>& path) {
	printf(">> ");
	int i = 0;
	for (i = 0; i < path.size() - 1; i++) {
		printf("[%d, %d] - ", path[i].x, path[i].y);
	}
	printf("[%d, %d]\n", path[i].x, path[i].y);
}

void dfs(int x, int y, int xn, int yn) {
	x = path.back().x, y = path.back().y;

	if (x == xn && y == yn) {
		display(visited);
		show_path(path);
		return;
	}
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k], ny = y + dy[k];

		if (0 <= nx && nx < N && 0 <= ny && ny < M)
			if (!visited[nx][ny] && map[nx][ny] == 0) {
				visited[nx][ny] = visited[x][y] + 1;
				path.push_back({ nx, ny });
				dfs(nx, ny, xn, yn);
				visited[nx][ny] = 0;
				path.pop_back();
			}
	}
}


void bfs(int x0, int y0, int xn, int yn) {
	queue<Data> Q;
	Q.push({ x0, y0, visited, path });	// visited[x0][y0] = 1;

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int x = cur.pos.x, y = cur.pos.y;

		if (x == xn && y == yn) {
			display(cur.visited);
			show_path(cur.path);
			continue;
		}
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k], ny = y + dy[k];

			if (0 <= nx && nx < N && 0 <= ny && ny < M)
				if (!cur.visited[nx][ny] && map[nx][ny] == 0) {
					cur.visited[nx][ny] = cur.visited[x][y] + 1;
					cur.path.push_back({ nx, ny });
					Q.push({ nx, ny, cur.visited, cur.path });
					cur.visited[nx][ny] = 0;
					cur.path.pop_back();
				}
		}
	}
}


int cal_dist(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void best_first_search(int x0, int y0, int xn, int yn) {
	priority_queue<Data> Q;
	Q.push({ x0, y0, visited, path, cal_dist(x0, y0, xn, yn) });

	while (!Q.empty()) {
		auto cur = Q.top(); Q.pop();
		int x = cur.pos.x, y = cur.pos.y;

		if (x == xn && y == yn) {
			display(cur.visited);
			show_path(cur.path);
			continue;
		}
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k], ny = y + dy[k];

			if (0 <= nx && nx < N && 0 <= ny && ny < M)
				if (!cur.visited[nx][ny] && map[nx][ny] == 0) {
					cur.visited[nx][ny] = cur.visited[x][y] + 1;
					cur.path.push_back({ nx, ny });
					Q.push({ nx, ny, cur.visited, cur.path, cal_dist(nx, ny, xn, yn) });
					cur.visited[nx][ny] = 0;
					cur.path.pop_back();
				}
		}
	}
}


int main()
{
	int x0 = 0, y0 = 5;		// start
	int xn = 6, yn = 6;		// goal

	printf("\n>> DFS\n");
	init(x0, y0);
	dfs(x0, y0, xn, yn);

	printf("\n>> BFS\n");
	init(x0, y0);
	bfs(x0, y0, xn, yn);

	printf("\n>> Best First Search\n");
	init(x0, y0);
	best_first_search(x0, y0, xn, yn);

	return 0;
}
```
