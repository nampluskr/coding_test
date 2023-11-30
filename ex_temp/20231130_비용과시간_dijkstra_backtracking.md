### [TC = 1] DFS / BFS / Dijkstra + Bracktracking

```cpp
#include <vector>
#include <queue>
using namespace std;

#define N 5	// Number of cities
#define INF 0xfffffff

struct City {
	int to, cost, time;
	vector<int> visited;
	vector<int> path;
	vector<int> timeList;

	City(int to, int cost, int time) {
		this->to = to, this->cost = cost, this->time = time;
		this->visited.clear(); this->visited.resize(N);
		this->path.clear();
		this->timeList.clear(); this->timeList.resize(N);
	}
	City(int to, int cost, int time, const vector<int>& visited, const vector<int>& path) {
		this->to = to, this->cost = cost, this->time = time;
		this->visited.clear(); this->visited.resize(N);
		for (int i = 0; i < N; i++) { this->visited[i] = visited[i]; }
		this->path.clear();
		for (int x : path) { this->path.push_back(x); }
		this->timeList.clear(); this->timeList.resize(N);
	}
	City(int to, int cost, int time, const vector<int>& visited, const vector<int>& path, const vector<int>& timeList) {
		this->to = to, this->cost = cost, this->time = time;
		this->visited.clear(); this->visited.resize(N);
		for (int i = 0; i < N; i++) { this->visited[i] = visited[i]; }
		this->path.clear();
		for (int x: path) { this->path.push_back(x); }
		this->timeList.clear(); this->timeList.resize(N);
		for (int i = 0; i < N; i++) { this->timeList[i] = timeList[i]; }
	}
	bool operator<(const City& city) const { return this->time > city.time; }

};
vector<City> cities[N];
vector<int> visited;
vector<int> path;
vector<int> timeList;

// (0 -> 1, time = 50, cost = 80)
// (1 -> 3, time = 20, cost = 70)
// (3 -> 4, time = 10, cost = 20)
// (1 -> 3, time = 60, cost = 10)
// (0 -> 2, time = 30, cost = 20)
// (2 -> 1, time = 40, cost = 40)

void add(int sCity, int eCity, int cost, int time) {
	cities[sCity].push_back({ eCity, cost, time });
}

void init(int sCity) {
	for (int i = 0; i < N; i++) { cities[i].clear(); }
	add(0, 2, 20, 30);
	add(0, 1, 80, 50);
	add(1, 3, 10, 60);
	add(1, 3, 70, 20);
	add(2, 1, 40, 40);
	add(3, 4, 20, 10);

	visited.clear(); visited.resize(N);
	visited[sCity] = 1;

	path.clear();
	path.push_back(sCity);

	timeList.clear(); timeList.resize(N);
	for (int i = 0; i < N; i++) { timeList[i] = INF; }
	timeList[sCity] = 0;
}

void print_path(const vector<int>& path) {
	int i;
	for (i = 0; i < path.size() - 1; i++)
		printf("[%d] - ", path[i]);
	printf("[%d]\n", path[i]);
}

void dfs(int to, int eCity, int cost, int time) {
	if (to == eCity) {
		print_path(path);
		printf(">> Total time = %3d, total cost = %3d\n\n", time, cost);
		return;
	}
	for (auto next : cities[to]) {
		if (!visited[next.to]) {
			visited[next.to] = 1;
			path.push_back(next.to);
			dfs(next.to, eCity, cost + next.cost, time + next.time);
			visited[next.to] = 0;
			path.pop_back();
		}
	}
}

void bfs(int sCity, int eCity) {
	queue<City> Q;	// to, cost, time, visited
	Q.push({ sCity, 0, 0, visited, path });

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();

		if (cur.to == eCity) {
			print_path(cur.path);
			printf(">> Total time = %3d, total cost = %3d\n\n", cur.time, cur.cost);
			continue;
		}
		for (auto next : cities[cur.to]) {
			if (!cur.visited[next.to]) {
				cur.visited[next.to] = 1;
				cur.path.push_back(next.to);
				Q.push({ next.to, cur.cost + next.cost, cur.time + next.time, cur.visited, cur.path });
				cur.visited[next.to] = 0;
				cur.path.pop_back();
			}
		}
	}
}

void dijkstra1(int sCity, int eCity) {
	priority_queue<City> Q;	// to, cost, time, visited
	Q.push({ sCity, 0, 0, visited, path, timeList });

	while (!Q.empty()) {
		auto cur = Q.top(); Q.pop();

		if (cur.to == eCity) {
			print_path(cur.path);
			printf(">> Total time = %3d, total cost = %3d\n\n", cur.time, cur.cost);
			continue;
		}
		if (cur.timeList[cur.to] < cur.time) continue;

		for (auto next : cities[cur.to]) {
			int temp_time = cur.timeList[next.to];
			//if (!cur.visited[next.to] && cur.timeList[next.to] > cur.timeList[cur.to] + next.time) {
			if (cur.timeList[next.to] > cur.timeList[cur.to] + next.time) {

				cur.timeList[next.to] = cur.timeList[cur.to] + next.time;
				cur.visited[next.to] = 1;
				cur.path.push_back(next.to);

				Q.push({ next.to, cur.cost + next.cost, cur.time + next.time, cur.visited, cur.path, cur.timeList });

				cur.visited[next.to] = 0;
				cur.path.pop_back();
				cur.timeList[next.to] = temp_time;;
			}
		}
	}
}

void dijkstra2(int M, int sCity, int eCity) {
	// [필수 정보]: to, cost, time, timeList (우선순위 time 이 적을 수록)
	priority_queue<City> Q;	// to, cost, time, visited, timeList
	Q.push({ sCity, 0, 0, visited, path, timeList });

	while (!Q.empty()) {
		auto cur = Q.top(); Q.pop();

		if (cur.to == eCity) {
			print_path(cur.path);
			printf(">> Total time = %3d, total cost = %3d\n\n", cur.time, cur.cost);
			continue;		// 계속 찾음
			//return;		// 찾으면 종료
		}
		if (cur.timeList[cur.to] < cur.time) continue;

		for (auto next : cities[cur.to]) {
			int temp_time = cur.timeList[next.to];
			if (cur.timeList[next.to] > cur.time + next.time) {
				if (cur.cost + next.cost < M) {

					cur.timeList[next.to] = cur.time + next.time;
					cur.path.push_back(next.to);
					Q.push({ next.to, cur.cost + next.cost, cur.time + next.time, cur.visited, cur.path, cur.timeList });
					cur.path.pop_back();
					cur.timeList[next.to] = temp_time;;
				}
			}
		}
	}
}

int main()
{
	//printf("[DFS] ====================\n");
	//init(0);
	//dfs(0, 4, 0, 0);	// sCity, ecity, cost, time
	//
	//printf("[BFS] ====================\n");
	//init(0);
	//bfs(0, 4);	// sCity, ecity, cost, time

	//printf("[Dijkstra-1] ====================\n");
	//init(0);
	//dijkstra1(0, 4);	// sCity, ecity, cost, time

	printf("[Dijkstra-2] (M = 200) ====================\n");
	init(0);
	dijkstra2(200, 0, 4);	// sCity, ecity, cost, time

	printf("[Dijkstra-2] (M = 120) ====================\n");
	init(0);
	dijkstra2(120, 0, 4);	// sCity, ecity, cost, time

	printf("[Dijkstra-2] (M = 100) ====================\n");
	init(0);
	dijkstra2(100, 0, 4);	// sCity, ecity, cost, time

	return 0;
}
```

### [231124_비용과시간] 풀이중 (Dijkstra + Bracktracking) - 풀이하고 나서 전자상가도 백트래킹으로 풀어볼 것 (DFS + Backtracking)

```cpp
#include <vector>
#include <queue>
using namespace std;

#define MAX_CITIES	100
#define INF	0xfffffff

int N;		// Number of cities

struct City {
	int to, cost, time;
	vector<int> visited;

	City(int to, int cost, int time) {
		this->to = to, this->cost = cost, this->time = time;
		this->visited.clear(); this->visited.resize(N);
	}
	City(int to, int cost, int time, const vector<int>& visitied) {
		this->to = to, this->cost = cost, this->time = time;
		this->visited.clear(); this->visited.resize(N);
		for (int i = 0; i < N; i++) { this->visited[i] = visited[i]; }
	}
	bool operator<(const City& city) const { return this->time > city.time; }
};
vector<vector<City>> cities;

vector<int> visited;
vector<int> timeList;
vector<int> costList;

//////////////////////////////////////////////////////////////////////////

void init(int _N, int K, int sCity[], int eCity[], int mCost[], int mTime[])
{
	N = _N;
	cities.clear(); cities.resize(N);
	visited.clear(); visited.resize(N);
	timeList.clear(); timeList.resize(N);
	costList.clear(); costList.resize(N);

	for (int i = 0; i < K; i++) {
		cities[sCity[i]].push_back({ eCity[i], mCost[i], mTime[i] });
	}
}

void add(int sCity, int eCity, int mCost, int mTime)
{
	int k = 0;
	cities[sCity].push_back({ eCity, mCost, mTime });
}

//  M 비용 내에서, sCity에서 eCity로 이동 최소 시간을 반환한다. 불가능하다면, -1을 반환한다.
int cost(int M, int sCity, int eCity)
{
	//priority_queue<City> Q;
	queue<City> Q;
	for (int i = 0; i < N; i++) { 
		visited[i] = 0;
		timeList[i] = INF;
		costList[i] = INF;
	}
	visited[sCity] = 1;
	timeList[sCity] = 0;
	costList[sCity] = 0;
	Q.push({ sCity, 0, 0, visited });	// to, cost, time

	printf("\n[%2d]->[%2d]: M = %3d\n", sCity, eCity, M);
	printf("===================================================\n");
	while (!Q.empty()) {
		//auto cur = Q.top(); Q.pop();
		auto cur = Q.front(); Q.pop();

		if (cur.to == eCity) {
			 printf(">> Reached!");
			//printf("[%2d] -> [%2d]: total time = %3d, total cost = %3d (%3d)\n", sCity, cur.to, cur.time, cur.cost, M);
			continue;
			//break;
		}

		if (timeList[cur.to] < cur.time) continue;

		for (const auto next : cities[cur.to]) {
			int temp_cost = costList[next.to];
			int temp_time = timeList[next.to];

			if (timeList[next.to] > timeList[cur.to] + next.time) {
			//if (!cur.visited[next.to]) {

			//cur.visited[next.to] = 1;
				costList[next.to] = costList[cur.to] + next.cost;
				timeList[next.to] = timeList[cur.to] + next.time;
				Q.push({ next.to, costList[next.to], timeList[next.to], cur.visited });

				printf("[%2d]->[%2d]: total time = %3d, total cost = %3d (M = %3d)\n", cur.to, next.to, timeList[next.to], costList[next.to], M);

				//Q.push({ next.to, costList[cur.to] + next.cost, timeList[cur.to] + next.time, cur.visited });
				//cur.visited[next.to] = 0;
				//costList[next.to] = temp_cost;
				//timeList[next.to] = temp_time;
				//Q.push({ next.to, costList[cur.to] + next.cost, timeList[cur.to] + next.time});
			}
		}
	}

	int ret = -1;
	if (timeList[eCity] != INF) { ret = timeList[eCity]; }
	return ret;
}
```
