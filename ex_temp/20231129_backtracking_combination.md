### [Combination - Selection] dfs / bfs

```cpp
#include <vector>
#include <queue>
using namespace std;

const int num = 3;
int cnt;

vector<int> list[num];
vector<int> selected;
vector<vector<int>> results;

void print_vector(const vector<int>& vec) {
	printf(">> ");
	for (int x : vec) { printf("%d, ", x); }
	printf("\n");
}

void dfs(int k, int sum) {
	cnt++;
	printf("[%2d] sum = %d\n", cnt, sum);

	if (k == num) {
		results.push_back(selected);
		print_vector(selected);
		return;
	}
	for (auto x : list[k]) {
		if (sum + x < 220) {
			selected.push_back(x);
			dfs(k + 1, sum + x);
			selected.pop_back();
		}
	}
}

struct Data {
	int k, sum;
	vector<int> selected;

	// deep copy
	Data(int k, int sum, const vector<int>& selected) {
		this->k = k;
		this->sum = sum;
		for (int x : selected) { this->selected.push_back(x); }
	}
};

void bfs() {
	queue<Data> Q;
	Q.push({ 0, 0, selected });

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int k = cur.k, sum = cur.sum;

		cnt++;
		printf("[%2d] sum = %d\n", cnt, sum);

		if (k == num) {
			results.push_back(cur.selected);
			print_vector(cur.selected);
			continue;
		}
		for (auto x : list[k]) {
			if (sum + x < 220) {
				cur.selected.push_back(x);
				Q.push({ k + 1, sum + x, cur.selected });
				cur.selected.pop_back();
			}
		}
	}
}


int main()
{
	list[0] = { 300, 200, 100 };
	list[1] = { 20, 10 };
	list[2] = { 3, 2, 1 };

	cnt = 0;
	bfs();

	return 0;
}
```
