# 230805_상품권배분

## 자료구조

```cpp
struct Node {};
unordered_map<int, int> nodeMap;
vector<Node> nodes;
int nodeCnt;

vector<int> groups;
int groupCnt;
```

```cpp
int get_nodeIndex(int mId) {}
void update_parents(int nIdx, int num) {}
void remove_children(int nIdx) {}    
```

## User Solution API

```cpp
void init(int N, int mId[], int mNum[]) {}
```
- N개의 그룹에 대한, 최상위 부서 ID와 부서 인원 수가 각각 배열로 주어진다.

```cpp
int add(int mId, int mNum, int mParent) {}
```
- mId 부서를 mParent 부서의 하위 부서로 추가한다. mId 부서의 인원 수는 mNum이다.
- mParent 값은 항상 존재하는 부서의 ID만 주어진다.
- mParent 부서에 이미 3개의 하위 부서가 존재한다면, 추가에 실패하고 -1을 반환한다.
- mId 값으로 이미 존재하는 부서의 ID가 주어지는 경우는 없다.

```cpp
int remove(int mId) {}
```
- ID가 mId인 부서를 삭제한다. mId 부서 아래 모든 부서도 함께 삭제된다.
- 최상위 부서의 ID가 주어지는 경우는 없다.
- 이미 삭제된 부서의 ID가 주어질 수도 있다.
- mId 부서가 존재하지 않을 경우, -1을 반환한다.

```cpp
int distribute(int K) {}
```
- N개의 그룹에 상품권 K개를 배분 규칙에 맞게 최대한 많이 나누어 주었을 때, 각 그룹에 배분된 상품권 개수 중에서 가장 큰 값을 반환한다.
