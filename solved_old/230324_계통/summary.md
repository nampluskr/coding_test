# 230324_계통

## 자료구조

```cpp
struct Node {};
unordered_map<string, int> nodeMap;
vector<Node> nodes;
int nodeCnt;
```

```cpp
int get_nodeIndex(char mSpecies[]) {}
int get_LCA(int x, int y) {}
```

## User Solution API

```cpp
void init(char mRootSpecies[MAXL]) {}
```
- 계통수에 mRootSpecies 이름을 가진 원시 종만 있다.

```cpp
void add(char mSpecies[MAXL], char mParentSpecies[MAXL]) {}
```
- 이름이 mParentSpecies인 종으로부터 진화하여 이름이 mSpecies 종이 생성되고 계통수에 추가된다.

```cpp
int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL]) {}
```
- 이름이 mSpecies1인 종과 이름이 mSpecies2인 종 간의 거리를 계산하고 그 값을 반환한다.

```cpp
int getCount(char mSpecies[MAXL], int mDistance)
```
- 이름이 mSpecies인 종으로부터 거리가 mDistance인 종의 개수를 세고 그 값을 반환한다.
