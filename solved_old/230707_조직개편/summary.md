# 230707_조직개편

## 자료구조

```cpp
struct Node{};
unordered_map<int, int> nodeMap;
vector<Node>nodes;
int nodeCnt;
```

```cpp
int get_nodeIndex(int mId) {}
void update_parents(int nIdx, int mNum) {}
void remove_children(int x) {}
```

## User Solution API

```cpp
void init(int mId, int mNum) {}
```
- mId 부서가 인원 수 mNum과 함께 주어진다. 이 부서가 최상위 부서가 된다.

```cpp
int add(int mId, int mNum, int mParent) {}
```
- mId 부서를 mParent 부서의 하위 부서로 추가한다. mId 부서의 인원 수는 mNum이다.
- mParent 값은 항상 존재하는 부서의 ID만 주어진다.
- mParent 부서에 이미 2개의 하위 부서가 존재한다면, 추가에 실패하고 -1을 반환한다.
- mId 값으로 이미 존재하는 부서의 ID가 주어지는 경우는 없다.

```cpp
int remove(int mId) {}
```
- ID가 mId인 부서를 삭제한다. mId 부서 아래 모든 부서도 함께 삭제된다.
- 최상위 부서의 ID가 주어지는 경우는 없다.
- 이미 삭제된 부서의 ID가 주어질 수도 있다.
- mId 부서가 존재하지 않을 경우, -1을 반환한다.

```cpp
int reorganize(int M, int K) {}
```
- 전체 부서를 M개의 그룹으로 나누었을 때, 각 그룹의 인원 수를 K명 이하로 만들 수 있는지 확인한다.
- 가능하다면 1을 반환하고, 불가능하다면 0을 반환한다.
