# 221210_최대최소값찾기

## 자료구조

```cpp
vector<int> values;
vector<int> states;
int totalCnt;
int cnt;

struct Data {};
struct Partition {};
Partition part;

int get_bucketIdx(int newIdx) {}
int get_valueIdx(int newIdx) {}
```

## User Solution API

```cpp
void init(int N, int mValue[]) {}
```
- N 은 초기 상태에 저장해야 할 수의 개수이다.
- mValue 에는 저장해야 할 수가 0번 인덱스부터 순서대로 저장되어 있다.

```cpp
void add(int M, int mValue[]) {}
```
- 새로운 수 M 개를 기존에 저장되어 있는 수의 오른쪽 끝에 저장한다.
- mValue 에는 저장해야 할 수가 0번 인덱스부터 순서대로 저장되어 있다.

```cpp
void erase(int mFrom, int mTo) {}
```
- 제일 앞에 있는 수를 1번째 수라고 정의했을 때, mFrom 번째 수부터 mTo 번째 수까지 삭제한다.
- 삭제 후 남아 있는 수들은 그 순서를 유지한다.

```cpp
int find(int K) {}
```
- 오른쪽 첫번째 수부터 K 번째까지의 수 중 가장 큰 수와 가장 작은 수의 차이를 반환한다.
