# 230617_호텔검색

## 자료구조

```cpp
struct Hotel {};
vector<Hotel> hotels;

struct Brand {};
vector<Brand> brands;

struct Data {};
vector<vector<Data>> graph;
vector<int> dist;     
```

```cpp
int dijkstra(int start, int brand, int visited) {}
```

## User Solution API

```cpp
void init(int N, int mBrands[]) {}
```
- N개의 지역에 호텔이 건설되며, 각 호텔의 ID는 0부터 N-1가 부여된다.
- 그리고, 해당 호텔을 소유한 회사의 브랜드의 ID가 호텔 ID 순서대로 주어진다.
- 다시 말해 호텔 ID의 i인 경우 이 호텔의 브랜드의 ID는 mBrands[i]가 된다.
- 브랜드의 ID는 0 ~ 49로 주어진다.
- 초기에는 지역 간에 연결된 도로가 전혀 없다.

```cpp
void connect(int mHotelA, int mHotelB, int mDistance) {}
```
- 호텔 mHotelA가 있는 지역과 호텔 mHotelB가 있는 지역을 연결하는 도로를 설치한다.
- 도로의 길이는 mDistance이다.

```cpp
int merge(int mHotelA, int mHotelB) {}
```
- 호텔 mHotelA가 속한 브랜드의 회사가 호텔 mHotelB가 속한 브랜드의 회사를 흡수 합병한다.
- 따라서 호텔 mHotelB가 속한 브랜드의 호텔들은 모두 mHotelA가 속한 브랜드로 변경된다.
- 합병 후, 호텔 mHotelA가 속한 브랜드를 가진 호텔의 개수를 반환한다.
- mHotelA와 mHotelB가 다름을 보장한다.
- mHotelA가 속한 브랜드와 mHotelB가 속한 브랜드가 동일한 경우 합병은 이루어지지 않고 해당 브랜드의 호텔 수만 반환한다.

```cpp
int move(int mStart, int mBrandA, int mBrandB) {}
```
- 경품에 당첨되어 투숙할 브랜드 mBrandA와 mBrandB가 주어진다.
- 호텔ID가 mStart인 호텔이 위치한 지역에서 당첨자는 출발한다.
- 가장 이동 비용이 적게 드는 해당 브랜드의 호텔들을 찾은 후, 비용을 발생시키는 이동거리의 최소 합을 반환한다.
- mBrandA와 mBrandB는 동일할 수 있으나, 선택되는 호텔들은 모두 달라야 한다.
- 선택되는 호텔들의 지역은 mStart가 있는 지역과 달라야 한다.
