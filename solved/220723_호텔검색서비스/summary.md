# 220723_호텔검색서비스

## 자료구조

```cpp
struct CheckInOut {};

struct Room {};
vector<Room> rooms;
//int roomCnt;

struct Hotel {};
vector<Hotel> hotels;
//int hotelCnt;

struct Data {};
priority_queue<Data> roomPQ[11][11][5][5];
```

## User Solution API

```cpp
void init(int N, int mRoomCnt[]) {}
```
- 호텔의 개수 N 은 최대 1,000 이다.
- mRoomCnt[] 는 각 호텔이 가지고 있는 룸의 개수를 전달하는 배열이다.
- mRoomCnt[k] 는 호텔 ID k+1 인 호텔이 보유하고 있는 룸의 개수 이다. (0 ≤ k ≤ N-1)

```cpp
void addRoom(int mHotelID, int mRoomID, int mRoomInfo[]) {}
```
- 호텔에 새로운 룸을 추가 한다.
- 룸을 추가할 호텔의 ID 값은 mHotelID 이다. 추가될 룸의 ID 값은 mRoomID 이다. 
- mRoomInfo 는 추가할 룸에 대한 정보이다. mRoomInfo 는 길이가 5인 배열이며, 각 인덱스에는 다음의 값을 포함한다.
- [0] : 지역, [1] : 침대 수, [2] : 룸 타입, [3] : 조망 타입, [4] : 가격

```cpp
int findRoom(int mFilter[]) {}
```
- 룸을 검색하고 예약한다. mFilter 는 검색 조건을 담고 있는 배열이다.
- [0] : 체크인 날짜, [1] : 체크아웃 날짜, [2] : 지역, [3] : 침대 수, [4] : 룸 타입, [5] : 조망 타입
- 체크인 ~ 체크아웃 기간에 이미 예약이 되어 있는 룸은 예약할 수 없다.
- 단, 체크아웃하는 날짜에, 다른 고객이 체크인 하는 것은 가능하다.
- 검색 조건에 맞는 룸 중, 가장 가격이 싼 룸을 예약한다.
- 가격이 같을 경우, 그 중 ID 값이 작은 룸을 선택한다.
- 예약한 룸의 ID 값을 반환한다. 예약 가능한 룸이 없다면 -1을 반환한다.

```cpp
int riseCosts(int mHotelID) {}
```
- 한 호텔이 보유하고 있는 모든 룸의 가격이 각각 10%씩 오른다. 계산시 소수점은 버린다.
