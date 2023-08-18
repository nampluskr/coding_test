# 230520_미생물가계도

## 자료구조

```cpp
struct Node {};
unordered_map<string, int> nodeMap;
vector<Node> nodes;
int nodeCnt;

struct Partition {};
Partition part;
```

```cpp
int get_nodeIndex(char mName[]) {}
int get_LCA(int x, int y) {}
```

## User Solution API

```cpp
void init(char mAncestor[], int mLastday) {}
```
- mAncestor는 선조의 이름이며, 선조의 생존 기간의 시작은 항상 0이다.

```cpp
int add(char mName[], char mParent[], int mFirstday, int mLastday) {}
```
- 이름이 mName인 새로운 미생물 개체의 정보가 추가된다. 기존에 중복된 이름이 없다는 것이 보장된다.
- 부모의 이름은 mParent이고, 개체의 생존 기간의 시작은 mFirstday, 마지막은 mLastday 이다.
- 이름이 mParent인 개체가 앞서 입력된 기록에 존재한다.
- 추가된 개체와 선조의 가계도 거리를 반환한다.

```cpp
int distance(char mName1[], char mName2[]) {}
```
- 이름이 mName1인 개체와 mName2인 개체 간의 가계도 거리를 반환한다.
- 이름이 mName1, mName2인 개체가 앞서 입력된 기록에 존재한다.

```cpp
int count(int mDay) {}
```
- 지금까지 기록된 미생물 중 생존 기간에 mDay일이 포함되는 개체 수를 반환한다.
