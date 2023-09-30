# 230624_단어미로

## 자료구조

```cpp
struct Room {};

unordered_map<string, int> roomMap;
vector<Room> rooms;
int current_mID;

unordered_map<string, priority_queue<Room>> dirMap[3];
```

## User Solution API

```cpp
void init() {}
```

```cpp
void addRoom(int mID, char mWord[], int mDirLen[]) {}
```
- 단어 미로에 방 번호가 mID 이고, mWord[] 단어가 있는 방이 추가된다.
- mDirLen[0]은 앞 방향 숫자를, mDirLen[1]은 중간 방향 숫자를, mDirLen[2]는 뒤 방향 숫자를 나타낸다.
- 앞 방향 숫자, 뒤 방향 숫자는 2 또는 4 이고, 중간 방향 숫자는 3 이다.
- mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.

```cpp
void setCurrent(char mWord[]) {}
```
- 단어 미로에 mWord[] 가 있는 방이 현재 위치가 된다.

```cpp
int moveDir(int mDir) { return 0; }
```
- 단어 미로의 현재 위치 방에서 mDir 방향으로 이동하고, 이동한 경우 이동한 방의 번호를 반환한다.
- mDir 방향으로 이동 가능한 방이 없어 이동이 실패할 경우 0 을 반환한다.
- 이동할 때 현재 위치 방은 제외되어, 다시 현재 위치 방으로 이동하지 않는다.
- mDir = 0: 앞 방향으로 이동한다. mDir = 1: 중간 방향으로 이동한다. mDir = 2: 뒤 방향으로 이동한다.

```cpp
void changeWord(char mWord[], char mChgWord[], int mChgLen[]) {}
```
- 단어 미로에서 단어가 mWord[] 인 방을 찾고, 그 방의 단어를 mChgWord[] 로 변경한다.
- 또한, mChgLen[0]은 앞 방향 숫자로, mChgLen[1]은 중간 방향 숫자로, mChgLen[2]는 뒤 방향 숫자로 변경한다.
