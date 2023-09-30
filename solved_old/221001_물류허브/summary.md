# 221001_물류허브

## 자료구조

```cpp
struct Data {};
unordered_map<int, int> cityMap;
vector<vector<Data>> cities;
int cityCnt;
```

```cpp
int get_cityIndex(int mCity) {}
int dijkstra(int start, int end) {}
```

## User Solution API

```cpp
int init(int N, int sCity[], int eCity[], int mCost[]) {}
```
- N개의 도로 정보가 주어진다. 각 도로의 출발 도시와 도착 도시, 운송 비용이 주어진다.
- 도로 정보로 주어지는 도시의 총 개수를 반환한다.
- 단방향 도로이기 때문에 출발 도시에서 도착 도시로만 갈 수 있다.
- 출발 도시와 도착 도시의 순서쌍이 동일한 도로는 없다. 출발 도시와 도착 도시가 서로 같은 경우는 없다.

```cpp
void add(int sCity, int eCity, int mCost) {}
```
- 출발 도시가 sCity이고, 도착 도시가 eCity이고, 운송 비용이 mCost인 도로를 추가한다.
- init()에 없던 새로운 도시는 주어지지 않는다.
- sCity에서 eCity로 가는 도로가 이미 존재하는 경우는 입력으로 주어지지 않는다.

```cpp
int cost(int mHub)
```
- mHub 도시에 물류 허브를 설치할 경우, 총 운송 비용을 계산하여 반환한다.
- mHub 도시의 운송 비용은 0으로 계산한다.