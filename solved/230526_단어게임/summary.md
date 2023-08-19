# 230526_단어게임

## 자료구조

```cpp
struct Card {};
struct PairHash {};
struct Data {};
struct Player {};

unordered_map<pair<string, string>, vector<int>, PairHash> cardMap;
priority_queue<Data> cardPQ;

vector<Card> cards;
vector<Player> players;
```

## User Solution API

```cpp
void init(int N, char mWordList[][], char mSubjectList[][]) {}
```
- 테스트 케이스에 대한 초기화 함수. 각 테스트 케이스의 맨 처음 1회 호출된다.
- 게임에서 사용되는 카드의 종류는 N개가 있고 각 종류의 카드는 1부터 N까지의 카드 번호로 구별된다.
- 카드 번호가 i인 카드에 적힌 단어와 주제어는 각각 mWordList[i – 1]와 mSubjectList[i – 1]이다. (1 ≤ i ≤ N)

```cpp
void join(int mID, int M, int mCardList[]) {}
```
- ID가 mID인 플레이어가 게임에 참가한다.
- 플레이어 mID가 참가할 때 플레이어 mID가 가진 카드의 개수는 M이고 가진 카드들은 mCardList[0] ~ mCardList[M – 1]로 주어진다. mCardList[]의 값은 카드 번호를 의미한다.
- 플레이어 mID의 초기 점수는 0이다. 가진 카드 중에 같은 카드가 여러 개 있을 수 있다.
- mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.

```cpp
int playRound(char mBeginStr[], char mSubject[]) {}
```
- 한 라운드가 진행된다. 그 라운드의 시작 문자열은 mBeginStr이고 주제어는 mSubject이다.
- 라운드 진행 과정은 본문 설명을 참고하라.
- 라운드가 끝나고 플레이어들이 제출한 카드의 번호를 모두 합한 값을 반환한다. 만약, 모든 플레이어가 제출한 카드가 없는 경우 0을 반환한다.

```cpp
int leave(int mID) {}
```
- ID가 mID인 플레이어가 게임을 떠나고 플레이어 mID가 얻은 점수를 반환한다.