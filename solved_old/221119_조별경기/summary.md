# 221119_조별경기

## 자료구조

```cpp
struct Player {};
vector<Player> players;

struct Team {};
vector<Team> teams;
```

## User Solution API

```cpp
void init(int N) {}
```
- N은 조별 경기에 참가한 선수들의 수이다.
- 모든 선수들은 1인 1조로 출전한다. 최초 모든 선수들의 점수는 0점이다.

```cpp
void updateScore(int mWinnerID, int mLoserID, int mScore) {}
```
- 서로 다른 두 조가 선정되어 경기를 진행하고 경기의 결과를 갱신하는 함수이다.
- ID가 mWinnerID인 선수가 속한 조가 승리하여 해당 조에 속한 선수들은 mScore의 점수를 얻는다.
- ID가 mLoserID인 선수가 속한 조가 패배하여 해당 조에 속한 선수들은 mScore의 점수를 잃는다.
- mWinnerID 선수와 mLoserID 선수의 조가 같은 경우는 주어지지 않는다.

```cpp
void unionTeam(int mPlayerA, int mPlayerB) {}
```
- 서로 다른 두 개의 조를 선정하여 하나의 조로 합치는 함수이다.
- ID가 mPlayerA인 선수가 속한 조와 ID가 mPlayerB인 선수가 속한 조를 하나의 조로 합친다.
- mPlayerA 선수와 mPlayerB 선수의 조가 같은 경우는 주어지지 않는다.

```cpp
int getScore(int mID) {}
```
- ID가 mID인 선수의 점수를 확인한다.
