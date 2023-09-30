#if 1
// STL 6572 ms
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define NUM_CITIES  600
#define INF INT32_MAX

struct Data {
    int x;
    int cost;
    bool operator<(const Data& data) const { return cost > data.cost; }
};
unordered_map<int, int> cityMap;
vector<vector<Data>> cities;
int cityCnt;

//////////////////////////////////////////////////////////////////////////////
int get_cityIndex(int mCity) {
    int cIdx;
    auto ptr = cityMap.find(mCity);
    if (ptr == cityMap.end()) {
        cIdx = cityCnt;
        cityMap[mCity] = cIdx;
        cityCnt += 1;
    }
    else { cIdx = ptr->second; }
    return cIdx;
}

int dijkstra(int start, int end) {
    priority_queue<Data> Q;
    vector<int> dist(cityCnt, INF);

    int ret = 0;
    dist[start] = 0;
    Q.push({ start, 0 });
    while (!Q.empty()) {
        auto node = Q.top(); Q.pop();

        if (node.x != start && node.x == end) {
            ret = dist[node.x];
            break;
        }
        if (dist[node.x] < node.cost) continue;

        for (const auto& next: cities[node.x]) {
            if (dist[next.x] > next.cost + node.cost) {
                dist[next.x] = next.cost + node.cost;
                Q.push({next.x, dist[next.x]});
            }
        }
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
int init(int N, int sCity[], int eCity[], int mCost[])
{
    cities.clear();  cities.resize(NUM_CITIES);
    cityCnt = 0;

    for (int i = 0; i < N; i++) {
        int sIdx = get_cityIndex(sCity[i]);
        int eIdx = get_cityIndex(eCity[i]);
        cities[sIdx].push_back({eIdx, mCost[i]});
    }
    return cityCnt;
}

void add(int sCity, int eCity, int mCost)
{
    int sIdx = get_cityIndex(sCity);
    int eIdx = get_cityIndex(eCity);

    cities[sIdx].push_back({ eIdx, mCost });
}

int cost(int mHub)
{
    int ret = 0;
    int hIdx = get_cityIndex(mHub);

    for (int i = 0; i < cityCnt; i++) {
        ret += dijkstra(i, hIdx);
        ret += dijkstra(hIdx, i);
    }
    return ret;
}
#endif