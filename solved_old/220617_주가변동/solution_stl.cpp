#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <cstring>
using namespace std;

#define MAX_STOCK_LEN 10
#define MAX_STOCKS	100000

struct Stock {
	char mStocks[MAX_STOCK_LEN + 1];
	int mPrice;
	int mPriceDiff;
};
vector<Stock> stocks;
int stockCnt;


//////////////////////////////////////////////////////////////////////////////
int get_stockIndex(const char mStock[]) {
	return -1;
}


//////////////////////////////////////////////////////////////////////////////
void init(int N, char mStocks[][MAX_STOCK_LEN + 1], int mPrices[])
{
	stocks.clear();	stocks.resize(N);
	int stockCnt = N;

	for (int i = 0; i < N; i++) {
		strcpy(stocks[i].mStocks, mStocks[i]);
		stocks[i].mPrice = mPrices[i];
	}
}

void changePrices(char mFromStock[], char mToStock[], int mPriceDiff)
{

}

int getPrice(char mStock[])
{
	return 0;
}

int getMostIncreasedStock(char mFromStock[], char mToStock[])
{
	return -1;
}