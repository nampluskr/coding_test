#if 0
// STL 593 ms
#include <queue>
#include <vector>
using namespace std;

#define NUM_AIRPORTS	60
#define INF		INT32_MAX	//	2147483647

struct Airline {
	int to;
	int start_time;
	int travel_time;
	int price;
};
vector<vector<Airline>> airlines;
int airportCnt;

struct TimeData {
	int to;
	int time;
	bool operator<(const TimeData& data) const { return time > data.time; }
};

struct PriceData {
	int to;
	int price;
	bool operator<(const PriceData& data) const { return price > data.price; }
};

/////////////////////////////////////////////////////////////////
void init(int N)
{
	airlines.clear();	airlines.resize(NUM_AIRPORTS);
	airportCnt = N;
}

// 3¸¸¹ø
void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
	airlines[mStartAirport].push_back({ mEndAirport, mStartTime, mTravelTime, mPrice });
}

// 1,000
int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
	int ret = -1;
	priority_queue<TimeData> Q;
	vector<int> cost(airportCnt, INF);

	Q.push({ mStartAirport, mStartTime });
	cost[mStartAirport] = mStartTime;

	while (!Q.empty())
	{
		auto data = Q.top(); Q.pop();
		int cur_to = data.to, cur_time = data.time;

		if (cur_to != mStartAirport && cur_to == mEndAirport) {
			ret = cur_time - mStartTime;
			break;
		}
		if (cur_time > cost[cur_to]) continue;

		for (const auto& next : airlines[cur_to]) {
			cur_time %= 24;
			int wait_time;

			if (cur_time > next.start_time)
				wait_time = 24 - (cur_time - next.start_time);
			else
				wait_time = next.start_time - cur_time;

			if (cost[next.to] > cost[cur_to] + wait_time + next.travel_time) {
				cost[next.to] = cost[cur_to] + wait_time + next.travel_time;
				Q.push({ next.to, cost[next.to] });
			}
		}
	}
	return ret;
}

// 5,000
int minPrice(int mStartAirport, int mEndAirport)
{
	int ret = -1;
	priority_queue<PriceData> Q;
	vector<int> cost(airportCnt, INF);

	Q.push({ mStartAirport, 0 });
	cost[mStartAirport] = 0;

	while (!Q.empty())
	{
		auto data = Q.top(); Q.pop();
		int cur_to = data.to, cur_price = data.price;

		if (cur_to != mStartAirport && cur_to == mEndAirport) {
			ret = cur_price;
			break;
		}
		if (cur_price > cost[cur_to]) continue;

		for (const auto& next : airlines[cur_to]) {
			if (cost[next.to] > cost[cur_to] + next.price) {
				cost[next.to] = cost[cur_to] + next.price;
				Q.push({ next.to, cost[next.to] });
			}
		}
	}
	return ret;
}
#endif