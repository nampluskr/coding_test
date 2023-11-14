#if 1
// STL 401 ms

#include <vector>
#include <queue>
using namespace std;

#define MAX_PARTS	4000
#define MAX_HOUSES	2
#define MAX_TYPES	3
#define MAX_BUDGET	500001

struct Part {
	int mType;
	int mPrice;
	int mPerformance;
	int mPosition;
};
Part parts[MAX_PARTS];
int partCnt;
int cnt[MAX_HOUSES][MAX_TYPES];

int mCharge;
int minPriceList[MAX_HOUSES + 1][MAX_TYPES];

struct Result {
	int mPrice;
	int mPerformance;
};

struct Data {
	int mPerformance;
	int pIdx;
	bool operator<(const Data& p) const { return mPerformance < p.mPerformance; }
};

////////////////////////////////////////////////////////////////////
void update_minPrice(const Part& p) {
	minPriceList[p.mPosition][p.mType] = min(minPriceList[p.mPosition][p.mType], p.mPrice);
	minPriceList[MAX_HOUSES][p.mType] = min(minPriceList[MAX_HOUSES][p.mType], p.mPrice);
}

int get_minPrice() {
	int ret = minPriceList[0][0] + minPriceList[0][1] + minPriceList[0][2];
	ret = min(ret, minPriceList[1][0] + minPriceList[1][1] + minPriceList[1][2]);
	ret = min(ret, minPriceList[MAX_HOUSES][0] + minPriceList[MAX_HOUSES][1] + minPriceList[MAX_HOUSES][2] + mCharge);
	return ret;
}

////////////////////////////////////////////////////////////////////
void init(int _mCharge)
{
	mCharge = _mCharge;
	partCnt = 0;

	for (int i = 0; i < MAX_HOUSES; i++)
		for (int j = 0; j < MAX_TYPES; j++) { cnt[i][j] = 0; }
}

// 4,000 입고된 창고에 동일한 type인 부품의 가짓수를 반환한다
int stock(int mType, int mPrice, int mPerformance, int mPosition)
{
	int pIdx = partCnt++;
	parts[pIdx] = { mType, mPrice, mPerformance, mPosition };
	cnt[mPosition][mType] += 1;

	int ret = cnt[mPosition][mType];
	return ret;
}

// 400
Result order(int mBudget)
{
	// 최소 가격 리스트 초기화
	for (int i = 0; i <= MAX_HOUSES; i++)
		for (int j = 0; j < MAX_TYPES; j++) { minPriceList[i][j] = MAX_BUDGET; }

	// Heap sort
	priority_queue<Data> Q;
	for (int i = 0; i < partCnt; i++) {
		Q.push({ parts[i].mPerformance, i });
	}

	// 최대 성능값에 대해 가격의 최소값을 구하고, mBudget 을 초과 하는지 체크한다.
	while (!Q.empty()) {
		auto data = Q.top(); Q.pop();
		update_minPrice(parts[data.pIdx]);
		int maxPerformance = data.mPerformance;

		// 만약 최대 성능을 내는 조합이 여러 개면 가장 가격이 낮은 조합으로 선택한다.
		while (!Q.empty() && Q.top().mPerformance == maxPerformance) {
			update_minPrice(parts[Q.top().pIdx]); Q.pop();
		}

		int minPrice = get_minPrice();
		if (minPrice <= mBudget) { 
			return { minPrice, maxPerformance };
		}
	}
	return { 0, 0 };
}
#endif