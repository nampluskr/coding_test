#pragma once

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
int visited[N][M];

int dx[] = { -1, 0, 1,  0 };
int dy[] = { 0, 1, 0, -1 };

struct Position {
	int x, y;
};

struct Data {
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


void display(const int map[N][M]) {
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) { printf("%2d ", map[i][j]); }
		printf("\n");
	}
}

void init(int x0, int y0) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
	visited[x0][y0] = 1;
}