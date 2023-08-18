# 210305_온라인서점

## 자료구조

```cpp
struct Book {};
struct Author {};
struct Data {};
struct Category {};

vector<Book> books;
vector<Author> authors;
vector<Category> categories;

priority_queue<Author> authorPQ;

```

## User Solution API

```cpp
void init(int N, int C) {}
```
- 각 테스트 케이스의 처음에 한번 호출되며, 저자의 수 N 과 책 카테고리의 수 C 가 전달된다.
- 초기 상태에서 모든 저자의 수익은 0 이다.

```cpp
void addBookInfo(int bID, int cID, int price, int num, int aIDs[]) {}
```
- 새로운 책의 정보를 Database 에 등록한다.
- 등록할 책의 ID는 bID 이고, 책의 카테고리 ID 는 cID 이며, 한 권당 가격은 price 이다.
- 책의 저자 수는 num 이며, 각각의 저자는 책이 한 권씩 팔릴 때 마다 책 가격의 1 / num 씩 수익금을 나누어 갖는다.
- 등록할 책의 ID 인 bID 는 1 부터 순서대로 주어진다

```cpp
void removeBookInfo(int bID) {}
```
- 책 bID 가 절판되어, Database 에 등록된 책 bID 의 정보를 삭제한다.

```cpp
void addBookStock(int bID, int cnt) {}
```
- Database 에 등록된 책 bID 의 재고를 cnt 권 추가로 확보한다.

```cpp
int sellBooks(int bID, int cnt) {}
```
- 책 bID 를 고객에게 cnt 권 판매한다. 판매가 성공 처리되었다면 1, 그렇지 않다면 0 을 반환한다.
- 책 bID 의 재고가 cnt 권 이상 남아 있다면 판매가 성공 처리되며 책의 재고가 cnt 권 감소한다. 만일 그렇지 않다면, 판매는 실패 처리된다.
- 책이 판매 될 경우, 판매된 책의 수익은 책의 저자에게 지급되며, 각각의 저자는 권당 [책의 가격 / 저자 수] 만큼의 수익을 얻게 된다.
- 책 bID 가 절판된 상태여도, 책의 재고가 cnt 권 이상 남아 있다면 판매가 가능하다.

```cpp
int getBestSeller(int cID, int bIDs[]) { return 0; }
```
- Database 에 등록된 책이면서, 카테고리 ID 가 cID 인 책들 중, 가장 판매량이 많은 책의 ID 들을 반환한다.
- 최대 3개 까지 반환할 수 있으며, 책의 ID 를 판매량이 가장 많은 순으로 bIDs[] 배열에 저장하여 반환한다.
- 만약 판매량이 같을 경우, 책의 ID 값이 더 큰 것이 우선이다.
- 단 cID = 0 일 경우, Database 에 등록된 모든 책들 중, 가장 판매량이 많은 책을 반환한다.
- bIDs[] 배열에는 절판 되지 않은 책들만 저장되어 있어야 함에 유의하라.

```cpp
void getBestAuthors(int aIDs[]) {}
```
- 모든 저자들 중, 가장 많은 수익을 올린 저자 3 명의 ID 를 반환하는 함수로 이때, 저자의 수익은 절판된 책에서 올린 수익도 포함한다.
- 3명의 저자 ID 를 수익이 많은 순으로 배치하되, 수익이 같다면 저자의 ID가 작은 것을 우선으로 aIDs[] 배열에 저장하여 반환한다.
