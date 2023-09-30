# 220408_미생물

## 자료구조

```cpp

```

## User Code

```cpp
void init(int N, char bNameList[][], int mHalfTime[])
```
- 처음 보관소는 비어있고, 현재 시각은 0 이다.
- 보관소에는 N 개 종류의 미생물을 보관할 수 있다.
- 미생물의 이름은 bNameList[] 이고, 미생물의 생명력이 절반으로 줄어드는 시간은 각각 mHalfTime[] 이다.

```cpp
void addBacteria(int tStamp, char bName[], int mLife, int mCnt)
```
- tStamp 시각에 mLife 생명력의 bName 미생물을 mCnt 개 보관한다.
- bName 미생물의 생명력은 tStamp 시각에 mLife 이고, 이후 mHalfTime 시간마다 현재 생명력이 절반으로 감소한다.

```cpp
int takeOut(int tStamp, int mCnt)
```
- tStamp 시각에 보관소에서 생명력이 가장 작은 순서로 미생물 mCnt 개 반출하고, 반출한 미생물의 생명력 합을 반환한다.
- 만약 미생물의 보관 개수가 mCnt 개 미만인 경우 보관중인 미생물을 모두 반출한다.
- 생명력이 같은 미생물이 있을 경우 보관 시각이 먼저인 미생물이 우선 반출된다.
- tStamp 시각에 생명력이 9 이하의 미생물은 폐기 처분되어 포함되지 않는다.

```cpp
int checkBacteria(int tStamp, char bName[])
```
- tStamp 시각에 보관소에 있는 bName 미생물의 개수를 반환한다.
- tStamp 시각에 생명력이 9 이하의 미생물은 폐기 처분되어 포함되지 않는다.
- 보관소에 bName 미생물의 개수가 0 일수도 있다.
