#if 0
// STL 553 ms
#include <vector>
#include <queue>
using namespace std;

#define INF INT32_MAX   // 2147483647

// 호텔, 브랜트
struct Hotel {
    int brand;
};
vector<Hotel> hotels;

struct Brand {
    vector<int> hotelList;
};
vector<Brand> brands;

struct Data {
    int x;
    int dist;
    bool operator<(const Data& data) const { return dist > data.dist; }
};
vector<vector<Data>> graph;
vector<int> dist;           // dist[x] start ~ x 까지 거리

///////////////////////////////////////////////////////////////////////////////
int dijkstra(int start, int brand, int visited) {
    priority_queue<Data> Q;
    fill(dist.begin(), dist.end(), INF);

    Q.push({start, 0});
    while (!Q.empty()) {
        auto node = Q.top(); Q.pop();   // x, dist

        if (node.x != start && hotels[node.x].brand == brand && node.x != visited) {
            return node.x;
        }
        if (dist[node.x] < node.dist) continue;

        for (const auto& next: graph[node.x])
            if (dist[next.x] > next.dist + node.dist) {
                dist[next.x] = next.dist + node.dist;
                Q.push({ next.x, dist[next.x] });
            }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////
void init(int N, int mBrands[])
{
    hotels.clear();     hotels.resize(N);
    brands.clear();     brands.resize(50);

    for (int i = 0; i < N; i++) {
        hotels[i].brand = mBrands[i];
        brands[mBrands[i]].hotelList.push_back(i);
    }
    graph.clear();  graph.resize(N);
    dist.clear();   dist.resize(N);
}

void connect(int mHotelA, int mHotelB, int mDistance)
{
    graph[mHotelA].push_back({ mHotelB, mDistance });
    graph[mHotelB].push_back({ mHotelA, mDistance });
}

int merge(int mHotelA, int mHotelB)
{
    int brandA = hotels[mHotelA].brand;
    int brandB = hotels[mHotelB].brand;

    if (brandA != brandB) {
        for (int hotelB : brands[brandB].hotelList) {
            hotels[hotelB].brand = brandA;
            brands[brandA].hotelList.push_back(hotelB);
        }
    }
    return brands[brandA].hotelList.size();
}

int move(int mStart, int mBrandA, int mBrandB)
{
    int hotelA = dijkstra(mStart, mBrandA, mStart);
    int distA = dist[hotelA];

    int hotelB = dijkstra(mStart, mBrandB, hotelA);
    int distB = dist[hotelB];

    return distA + distB;
}
#endif