#include <vector>
#include <queue>
using namespace std;

#define NUM_AIRPORTS 60
#define INF INT32_MAX   // 2147483647

struct TimeData {
    int x;
    int start_time;
    int travel_time;
    int time;
    bool operator<(const TimeData& data) const { return time > data.time; }
};
struct PriceData {
    int x;
    int price;      // start -> end (travel price)
    bool operator<(const PriceData& data) const { return price > data.price; }
};

struct Airport {
    int start_time;
    vector<TimeData> timeList;
    vector<PriceData> priceList;
};

vector<Airport> airports;
int airportCnt;

//////////////////////////////////////////////////////////////////////////////
void init(int N)
{
    airports.clear(); airports.resize(NUM_AIRPORTS);
    airportCnt = N;
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
    airports[mStartAirport].timeList.push_back({ mEndAirport, mStartTime, mTravelTime });
    airports[mStartAirport].priceList.push_back({ mEndAirport, mPrice });
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
    int ret = -1;
    priority_queue<TimeData> Q;
    vector<int> time(airportCnt, INF);

    time[mStartAirport] = mStartTime;
    Q.push({ mStartAirport, mStartTime, 0, 0 });

    while (!Q.empty()) {
        auto current = Q.top(); Q.pop();

        if (current.x != mStartAirport && current.x == mEndAirport) {
            ret = current.time;
            break;
        }
        if (time[current.x] < current.time) continue;

        for (auto next : airports[current.x].timeList) {
            int current_time = current.time % 24;
            int wait_time;

            if (current_time > next.start_time) { 
                wait_time = 24 - (current_time - next.start_time);
            }
            else { wait_time = next.start_time - current_time; }

            if (time[next.x] > time[current.x] + wait_time + next.time) {
                time[next.x] = time[current.x] + wait_time + next.time;
                Q.push({ next.x, next.start_time, next.travel_time, time[next.x] });
            }
        }
    }
    //if (time[mEndAirport] != INF) { ret = time[mEndAirport]; }
    return ret;
}

int minPrice(int mStartAirport, int mEndAirport)
{
    int ret = -1;
    priority_queue<PriceData> Q;
    vector<int> price(airportCnt, INF);

    price[mStartAirport] = 0;
    Q.push({ mStartAirport, 0 });

    while (!Q.empty()) {
        auto current = Q.top(); Q.pop();

        if (current.x != mStartAirport && current.x == mEndAirport) {
            ret = current.price;
            break;
        }
        if (price[current.x] < current.price) continue;

        for (auto next : airports[current.x].priceList) {
            if (price[next.x] > price[current.x] + next.price) {
                price[next.x] = price[current.x] + next.price;
                Q.push({ next.x, price[next.x] });
            }
        }
    }
    //if (price[mEndAirport] != INF) { ret = price[mEndAirport]; }
    return ret;
}