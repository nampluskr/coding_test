#include <vector>
using namespace std;

#define NUM_CITIES      200 // 0 ~ N-1
#define NUM_OFFICIERS   50

// ���ô� N���� ������, ������ ID�� �ߺ����� 0 ~ N - 1 �� �ο��ȴ�.
// ������ ID �� 0 �̸�, ������ �������� ���� ��ȣ�� ID�� �ο��ȴ�.
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
// tStamp �ð��� ���� mCityA �� mTax ��ŭ�� ��� ���� mCityB �� �����϶�� ����� ������.
// ���� mCityA ���� � mTax ��ŭ�� ���� mCityB �� �̵� ��Ų��.
// ���ÿ� ���� ���ÿ��� �̵��� 1�ð��� �ҿ�ȴ�.
int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    return -1;
}

// 10,000
// tStamp �ð� ���� ������ �ִ� ��� ���� ��ȯ�Ѵ�.
int check(int tStamp)
{
    return -1;
}