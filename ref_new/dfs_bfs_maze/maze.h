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

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct Position {
	int row, col;
};

struct Data {
	Position pos;
	int dist;
	int visited[N][M];	// deep copied

	// for queue<Position>
	Data(int row, int col, const int visited[N][M]) {
		this->pos.row = row, this->pos.col = col, this->dist = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				this->visited[i][j] = visited[i][j];
		
	}
	// for priority_queue<Position>
	Data(int row, int col, int dist, const int visited[N][M]) {
		Data(row, col, visited);
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

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
}