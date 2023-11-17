#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

#define MAX_STOCK_LEN 10
#define MAX_N 100000

#define CMD_CHANGE_PRICES 100
#define CMD_GET_PRICE 200
#define CMD_GET_MOST_INCREASED_STOCK 300

extern void init(int N, char mStocks[][MAX_STOCK_LEN + 1], int mPrices[]);
extern void changePrices(char mFromStock[], char mToStock[], int mPriceDiff);
extern int getPrice(char mStock[]);
extern int getMostIncreasedStock(char mFromStock[], char mToStock[]);

static char mStocks[MAX_N][MAX_STOCK_LEN + 1];
static int mPrices[MAX_N];

static bool run()
{
	int N, M;
	bool ok = false;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", mStocks[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &mPrices[i]);
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		if (i == 0)
		{
			init(N, mStocks, mPrices);
			ok = true;
		}

		int command;
		scanf("%d", &command);

		char mFromStock[MAX_STOCK_LEN + 1];
		char mToStock[MAX_STOCK_LEN + 1];
		char mStock[MAX_STOCK_LEN + 1];
		int ret = 0, ans = 0, mPriceDiff = 0;

		switch (command)
		{
		case CMD_CHANGE_PRICES:
			scanf("%s", mFromStock);
			scanf("%s", mToStock);
			scanf("%d", &mPriceDiff);
			changePrices(mFromStock, mToStock, mPriceDiff);
			break;

		case CMD_GET_PRICE:
			scanf("%s", mStock);
			ret = getPrice(mStock);
			scanf("%d", &ans);
			if (ans != ret)
			{
				ok = false;
			}
			break;

		case CMD_GET_MOST_INCREASED_STOCK:
			scanf("%s", mFromStock);
			scanf("%s", mToStock);

			ret = getMostIncreasedStock(mFromStock, mToStock);
			scanf("%d", &ans);
			if (ans != ret)
			{
				ok = false;
			}
			break;
		}
	}
	return ok;
}

int main()
{
	clock_t start = clock();

	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d%d", &T, &MARK);
	for (int tc = 1; tc <= T; tc++)
	{
		clock_t tc_start = clock();
		int score = run() ? MARK : 0;
		int tc_result = (clock() - tc_start) / (CLOCKS_PER_SEC / 1000);
		printf("#%2d %d (%3d ms)\n", tc, score, tc_result);
	}
	int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf(">> Result: %d ms\n", result);

	return 0;
}