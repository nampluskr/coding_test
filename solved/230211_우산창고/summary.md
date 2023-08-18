# 230211_우산창고

## 자료 구조
```cpp
struct Data {};
struct Node {};
vector<Node> nodes;             // NUM_NODES, nodeCnt
vector<vector<Data>> graph;     // NUM_NODES, nodeCnt
```

## 사용자 정의 함수

```cpp
int get_LCA(int x, int y) {}
```
```cpp
void update_parents(int mIdx, int quantity) {}
``````

## User Code API

```cpp
void init(int N, int mParent[], int mDistance[], int mQuantity[]) {}
```
- 어떤 창고에서 출발하든, 50개 이하의 도로를 거쳐 0번 창고에 도달할 수 있음이 보장된다.

```cpp
int carry(int mFrom, int mTo, int mQuantity) { return 0; }
```
- `mFrom`번 창고에서 `mTo`번 창고로 `mQuantity`개의 우산을 최단 경로로 옮긴다.
- 지불한 비용을 반환한다.

```cpp
int gather(int mID, int mQuantity) { return 0; }
```
- `mID`번 창고가 다른 창고들에게 총 `mQuantity`개의 우산을 보내달라고 요청한다.
- 우선순위가 높은 창고에 있는 우산부터 옮긴다.
  1. `mID`번 창고와의 거리가 가까운 순
  2. `mID`번 창고와의 거리가 같을 경우, 고유 번호가 작은 순
- 우산은 항상 최단 경로로 옮긴다.
- 지불한 비용을 반환한다.


```cpp
int sum(int mID) { return 0; }
```
- `mID`번 창고의 자손 창고들에 있는 우산의 총 개수를 반환한다.
