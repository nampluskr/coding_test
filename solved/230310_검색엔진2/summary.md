# 230310_검색엔진2

## 자료구조

```cpp
struct Result {};
struct Word {};
struct Group {};

unordered_map<string, int> wordMap;
vector<Word> words;
vector<Group> groups;
int wordCnt;

struct Data {};
```

```cpp
int get_wordIndex(char mStr[]) {}
vector<int> get_topk(char prefix[], int k) {}
```

## User Solution API

```cpp
void init() {}
```

```cpp
void search(char mStr[], int mCount) {}
```
- 연관검색어 관계를 고려해 검색어 mStr의 조회수를 mCount 만큼 증가시켜 반영한다.
- 동일한 mStr로 여러 번 조회수가 누적될 수 있다.

```cpp
Result recommend(char mStr[]) { result { 0, 0 };}
```
- 사용자가 mStr을 추천 검색어 기능을 사용하여 검색하고자 한다.
- 추천 검색어에 처음으로 mStr이 등장하는 위치를 반환하라.
- [Fig. 1]과 같은 경우 ‘ab’를 입력하면 2번째로 추천되므로, Result 구조체의 mRank와 mOrder가 각각 2가 된다.
- 이 함수로 검색한 후 해당 검색어의 조회수가 ‘1’ 증가한다.

```cpp
int relate(char mStr1[], char mStr2[]) {}
```
- 검색어 mStr1과 검색어 mStr2를 연관 검색어로 설정한다.

```cpp
void rank(char mPrefix[], int mRank, char mReturnStr[]) {}
```
- mPrefix로 시작하는 검색어 중 mRank 번째 많이 조회된 검색어를 찾아 mReturnStr에 반환한다.
- 같은 조회수이면 사전 순서로 앞서는 검색어가 우선한다.
