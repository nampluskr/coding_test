#include <vector>
using namespace std;

#define NUM_CITIES      200 // 0 ~ N-1
#define NUM_OFFICIERS   50

// 도시는 N개가 있으며, 도시의 ID는 중복없이 0 ~ N - 1 로 부여된다.
// 수도는 ID 는 0 이며, 수도에 가까울수록 낮은 번호의 ID가 부여된다.
struct City {

};
vector<City> cities;
int cityCnt;

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
void init(int N, int M)
{
    cities.clear(); cities.resize(NUM_CITIES);
    cityCnt += 1;
}

void destroy() {}

// 10,000
// tStamp 시각에 도시 mCityA 에 mTax 만큼의 곡물을 도시 mCityB 로 납부하라는 명령을 내린다.
// 도시 mCityA 에서 곡물 mTax 만큼을 도시 mCityB 로 이동 시킨다.
// 도시와 인접 도시와의 이동은 1시각이 소요된다.
int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    return -1;
}

// 10,000
// tStamp 시각 현재 수도에 있는 곡물의 양을 반환한다.
int check(int tStamp)
{
    return -1;
}