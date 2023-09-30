# 230429_블록쌓기게임

## 자료구조

```cpp
struct Result {};
struct Data {};
struct Partition {};

Partition part;
```

## User Solution API

```cpp
void init(int C) {}
```
- 격자판의 열의 개수 C가 주어진다. 처음 격자판은 비어있다.

```cpp
Result dropBlocks(int mCol, int mHeight, int mLength) {}
```
- 격자판의 가로방향의 위치 mCol에 높이가 mHeight이고 길이가 mLength인 직사각형 모양으로 배치된 블록들을 위치시킨다.
- 격자판을 벗어나서 블록들이 위치하게 하는 mCol와 mLength 값이 주어지는 경우는 없다.
- 배치된 블록들이 아래로 내려가다 멈추게 되면 각 행마다 블록들로 가득 찼는지 여부를 확인하여 해당 행의 블록들을 삭제하고 위쪽의 블록들을 밑으로 내린다.
- 이후 남아있던 블록들의 개수를 1,000,000으로 나눈 나머지와 가장 높은 블록의 높이를 반환한다.
