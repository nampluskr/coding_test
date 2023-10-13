### [물품보관]

```cpp
#include<vector>
using namespace std;

#define MaxVacancy 100'001

int arr[MaxVacancy];

struct Info {
  int max;
  int id;
};

Info max(Info A, Info B) {
  if (A.max > B.max)
    return A;
  return B;
}

struct Segtree {
  vector<Info> tree;
  void resize(int N) {
    tree.clear();
    tree.resize(N * 4 + 1);
  }

  void update(int n, int s, int e, int idx) {
    if (e < idx or idx < s) {
      return;
    }
    if (s == idx and idx == e) {
      tree[n].max = arr[idx];
      tree[n].id = idx;
      return;
    }
    int mid = (s + e) / 2;
    update(n * 2, s, mid, idx);
    update(n * 2 + 1, mid + 1, e, idx);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
  }

  Info query(int n, int s, int e, int left, int right) {
    if (e < left or right < s)
      return { 0, 0 };
    if (left <= s and e <= right)
      return tree[n];

    int mid = (s + e) / 2;
    return max(query(n * 2, s, mid, left, right), query(n * 2 + 1, mid + 1, e, left, right));
  }
}segtree;

int N;

void init(int _N){
  N = _N;
  for (int i = 0; i < N; i++)
    arr[i] = 0;
  segtree.resize(N);
  return;
}

int getBlockNumLeft(int id) {
  int ret = 0;
  auto left = segtree.query(1, 0, N-1, 0, id);
  ret += (id - left.id + 1) * left.max;
  if (left.id == 0)
    return ret;
  ret += getBlockNumLeft(left.id - 1);
  return ret;
}

int getBlockNumRight(int id) {
  int ret = 0;
  if (id == N-1)
    return segtree.query(1, 0, N - 1, id, N - 1).max;

  auto right = segtree.query(1, 0, N-1, id, N-1);
  if (right.id < id)
    return 0;
  ret += (right.id - id + 1) * right.max;
  if (right.id == N - 1)
    return ret;

  ret += getBlockNumRight(right.id + 1);
  return ret;
}

int stock(int mLoc, int mBox){
  int ret = 0;
  arr[mLoc-1] += mBox;
  segtree.update(1, 0, N-1, mLoc-1);

  ret += segtree.tree[1].max;
  ret += getBlockNumLeft(segtree.tree[1].id - 1);
  ret += getBlockNumRight(segtree.tree[1].id + 1);
  return ret;
}

int ship(int mLoc, int mBox)
{
  int ret = 0;
  arr[mLoc - 1] -= mBox;
  segtree.update(1, 0, N - 1, mLoc - 1);
  ret += segtree.tree[1].max;
  ret += getBlockNumLeft(segtree.tree[1].id - 1);
  ret += getBlockNumRight(segtree.tree[1].id + 1);

  return ret;
}

int getHeight(int mLoc)
{
  return arr[mLoc - 1];
}
```

### [승강제리그]

```cpp
#include <queue>
#include <vector>
using namespace std;

#define MaxLeague 10

struct Player {
  int ability;
  int id;
  int state;
};

struct maxCmp {
  bool operator()(const Player& A, const Player& B) {
    if (A.ability == B.ability) {
      return A.id > B.id;
    }
    return A.ability < B.ability;
  }
};

struct minCmp {
  bool operator()(const Player& A, const Player& B) {
    if (A.ability == B.ability) {
      return A.id < B.id;
    }
    return A.ability > B.ability;
  }
};

vector<Player> player;
priority_queue <Player, vector<Player>, maxCmp> max_pq[MaxLeague];
priority_queue <Player, vector<Player>, minCmp> min_pq[MaxLeague];
priority_queue <Player, vector<Player>, minCmp> frontmin_pq[MaxLeague];
priority_queue <Player, vector<Player>, maxCmp> backmax_pq[MaxLeague];
priority_queue <Player, vector<Player>, maxCmp> temp_pq;

Player temp;

Player maxvalue(int i) {
  while (max_pq[i].size()) {
    temp = max_pq[i].top();
    max_pq[i].pop();
    if (temp.state == player[temp.id].state)
      break;
  }
  player[temp.id].state++;
  return player[temp.id];
}

Player minvalue(int i) {
  while (min_pq[i].size()) {
    temp = min_pq[i].top();
    min_pq[i].pop();
    if (temp.state == player[temp.id].state)
      break;
  }
  player[temp.id].state++;
  return player[temp.id];
}

Player midvalue(int i) {
  while (frontmin_pq[i].size()) {
    temp = frontmin_pq[i].top();
    frontmin_pq[i].pop();
    if (temp.state == player[temp.id].state) {
      frontmin_pq[i].push(temp);
      break;
    }
  }
  while (backmax_pq[i].size()) {
    temp = backmax_pq[i].top();
    backmax_pq[i].pop();
    if (temp.state == player[temp.id].state)
      break;
  }
  player[temp.id].state++;
  return player[temp.id];
}

void update(int i, Player A, int add) {
  if (frontmin_pq[i].empty()) {
    temp_pq.push(A);
    temp_pq.push(backmax_pq[i].top());
    backmax_pq[i].pop();

    frontmin_pq[i].push(temp_pq.top());
    temp_pq.pop();
    backmax_pq[i].push(temp_pq.top());
    temp_pq.pop();
    return;
  }

  temp_pq.push(A);
  temp_pq.push(frontmin_pq[i].top());
  frontmin_pq[i].pop();
  temp_pq.push(backmax_pq[i].top());
  backmax_pq[i].pop();

  if (add) {
    frontmin_pq[i].push(temp_pq.top());
    temp_pq.pop();

    frontmin_pq[i].push(temp_pq.top());
    temp_pq.pop();

    backmax_pq[i].push(temp_pq.top());
    temp_pq.pop();

    return;
  }
  frontmin_pq[i].push(temp_pq.top());
  temp_pq.pop();
  backmax_pq[i].push(temp_pq.top());
  temp_pq.pop();
  backmax_pq[i].push(temp_pq.top());
  temp_pq.pop();
}
vector<Player> maxPlayerList;
vector<Player> minPlayerList;

int N, L;

void init(int _N, int _L, int mAbility[]) {
  N = _N;
  L = _L;
  player.clear();

  for (int i = 0; i < L; i++) {
    while (max_pq[i].size())
      max_pq[i].pop();
    while (min_pq[i].size())
      min_pq[i].pop();
    while (frontmin_pq[i].size())
      frontmin_pq[i].pop();
    while (backmax_pq[i].size())
      backmax_pq[i].pop();
  }
  int nump;

  for (int i = 0; i < N; i++) {
    nump = i / (N / L);
    max_pq[nump].push({ mAbility[i], i, 0 });
    min_pq[nump].push({ mAbility[i], i, 0 });
    backmax_pq[nump].push({ mAbility[i], i, 0 });
    player.push_back({ mAbility[i], i, 0 });
  }
  for (int i = 0; i < L; i++) {
    while (backmax_pq[i].size() > (N / L + 1) / 2) {
      frontmin_pq[i].push(backmax_pq[i].top());
      backmax_pq[i].pop();
    }
  }
}

int move() {
  int sum = 0;
  maxPlayerList.clear();
  minPlayerList.clear();

  for (int i = 0; i < L - 1; i++) {
    maxPlayerList.push_back(maxvalue(i + 1));
    minPlayerList.push_back(minvalue(i));
  }

  for (int i = 0; i < L - 1; i++) {
    max_pq[i].push(maxPlayerList[i]);
    min_pq[i].push(maxPlayerList[i]);
    update(i, maxPlayerList[i], 0);
    sum += maxPlayerList[i].id;

    max_pq[i + 1].push(minPlayerList[i]);
    min_pq[i + 1].push(minPlayerList[i]);
    update(i + 1, minPlayerList[i], 1);
    sum += minPlayerList[i].id;
  }
  return sum;
}

int trade() {
  int sum = 0;
  maxPlayerList.clear();
  minPlayerList.clear();

  for (int i = 0; i < L - 1; i++) {
    maxPlayerList.push_back(maxvalue(i + 1));
    minPlayerList.push_back(midvalue(i));
  }
  for (int i = 0; i < L - 1; i++) {
    max_pq[i].push(maxPlayerList[i]);
    min_pq[i].push(maxPlayerList[i]);
    update(i, maxPlayerList[i], 0);
    sum += maxPlayerList[i].id;

    max_pq[i + 1].push(minPlayerList[i]);
    min_pq[i + 1].push(minPlayerList[i]);
    update(i + 1, minPlayerList[i], 1);
    sum += minPlayerList[i].id;
  }
  return sum;
}
```
