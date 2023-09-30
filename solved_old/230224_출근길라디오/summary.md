# 230224_출근길라디오

## 자료구조

```cpp
struct Road {};
vector<Road> roads;
int roadCnt;

struct Type {};
vector<Type> types;

struct Partition {};
Partition part;
```

## User Solution API

```cpp
void init(int N, int M, int mType[], int mTime[]) {}
```
- 지점은 N 개가 있다. 구간은 N-1개가 있고, 각 구간의 도로의 종류는 M개가 있다.
- 지점의 ID는 도로의 시작 지점부터 순서대로 0 ~ N – 1 이고,
- 구간의 ID는 도로의 시작 지점에 가까운 순서대로 0 ~ N – 2 이다.

```cpp
void destroy() {}
```

```cpp
void update(int mID, int mNewTime)
```
- 구간 mID 의 통과시간이 mNewTime으로 변경된다.

```cpp
int updateByType(int mTypeID, int mRatio256) { return 0; }
```
- 도로의 종류가 mTypeID 인 구간들의 모든 도로의 통과 시간이 mRatio256 / 256 의 비율로 변경되며, 변경 이후 소수점 이하는 버린다.
- 변경된 모든 구간의 통과 시간의 합을 반환한다.

```cpp
int calculate(int mA, int mB) { return 0;}
```
- 지점 mA 에서 지점 mB 까지 이동하는 데 예상되는 소요 시간을 반환 한다.
