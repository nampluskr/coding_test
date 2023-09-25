#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif 

#include <stdio.h> 
#include <time.h>

#define ADDRATE 45 
#define REMOVERATE 50 
#define SEARCH1RATE 90 
#define SEARCH2RATE 100 

extern void init(int n);
extern void addFacility(int mId, int mType, int mY, int mX);
extern void removeFacility(int mId);
extern int search1(int mType, int mY, int mX, int mRadius);
extern void search2(int mType, int mY, int mX, int mIdList[5]);

static int seed; static int radiusTb[5050], K;

static int pseudo_rand(void)
{
	seed = seed * 431345 + 2531999;
	return seed & 0x7FFFFFFF;
}

static bool run()
{
	int N, M, initAdd;
	int id = 1;
	bool removeChk[50000] = { 0 };
	bool isCorrect = true;
	scanf("%d%d%d%d", &seed, &N, &M, &initAdd);


	if (N >= 100)
	{
		K = 5050;
	}
	else
	{
		K = 0;
		for (int i = 1; i <= 100; ++i)
		{
			if (radiusTb[K] > N)
			{
				break;
			}
			K += i;
		}
	}
	init(N);
	for (int i = 0; i < N * initAdd; ++i)
	{
		int type = pseudo_rand() % 10 + 1;
		int y = pseudo_rand() % N + 1;
		int x = pseudo_rand() % N + 1;
		addFacility(id++, type, y, x);
	} while (M--)
	{
		int cmd = pseudo_rand() % 100;
		if (cmd < ADDRATE)
		{
			int type = pseudo_rand() % 10 + 1;
			int y = pseudo_rand() % N + 1;
			int x = pseudo_rand() % N + 1;
			addFacility(id++, type, y, x);
		}
		else if (cmd < REMOVERATE)
		{
			int removeId = pseudo_rand() % (id - 1) + 1;
			while (removeChk[removeId])
			{
				removeId = pseudo_rand() % (id - 1) + 1;
			}
			removeFacility(removeId);
			removeChk[removeId] = true;
		}
		else if (cmd < SEARCH1RATE)
		{
			int type = pseudo_rand() % 11;
			int y = pseudo_rand() % N + 1;
			int x = pseudo_rand() % N + 1;
			int radius = pseudo_rand() % K;
			int ret, ans; ret = search1(type, y, x, radiusTb[radius]);
			scanf("%d", &ans);
			if (ret != ans)
			{
				isCorrect = false;
			}
		}
		else
		{

			if (M == 2937) {
				int k = 0;
			}

			int type = pseudo_rand() % 10 + 1;
			int y = pseudo_rand() % N + 1;
			int x = pseudo_rand() % N + 1;
			int ret[5] = { 0 };
			int ansN, ans; search2(type, y, x, ret);
			scanf("%d", &ansN);
			for (int i = 0; i < ansN; ++i)
			{
				scanf("%d", &ans);
				if (ret[i] != ans)
				{
					isCorrect = false;
				}
			}
			for (int i = ansN; i < 5; ++i)
			{
				if (ret[i] != 0)
				{
					isCorrect = false;
				}
			}
		}
	}
	return isCorrect;
}

int main(void)
{
	clock_t start = clock();

	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int test, T;
	int answerScore;
	scanf("%d", &T); scanf("%d", &answerScore);

	for (int i = 1; i <= 100; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			radiusTb[K++] = i;
		}
	}
	for (test = 1; test <= T; ++test)
	{
		if (run()) {
			printf("#%d %d\n", test, answerScore);
		}
		else {
			printf("#%d 0\n", test);
		}
	}
	int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf(">> Result: %d ms\n", result);

	return 0;
}