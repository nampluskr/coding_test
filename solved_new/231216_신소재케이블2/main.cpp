#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>;
#include <time.h>

#define CMD_INIT		(100)
#define CMD_CONNECT		(200)
#define CMD_MEASURE		(300)
#define CMD_TEST		(400)

extern void init(int mDevice);
extern void connect(int mOldDevice, int mNewDevice, int mLatency);
extern int measure(int mDevice1, int mDevice2);
extern int test(int mDevice);

static bool run()
{
	int Q;
	int mDevice, mOldDevice, mNewDevice, mDevice1, mDevice2;
	int mLatency;
	int ret = -1, ans;

	scanf("%d", &Q);
	bool okay = false;

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d", &mDevice);
			init(mDevice);
			okay = true;
			break;

		case CMD_CONNECT:
			scanf("%d %d %d", &mOldDevice, &mNewDevice, &mLatency);
			connect(mOldDevice, mNewDevice, mLatency);
			break;

		case CMD_MEASURE:
			scanf("%d %d", &mDevice1, &mDevice2);
			ret = measure(mDevice1, mDevice2);
			scanf("%d", &ans);
			if (ret != ans) {
				okay = false;
			}
			break;

		case CMD_TEST:
			scanf("%d", &mDevice);
			ret = test(mDevice);
			scanf("%d", &ans);
			if (ret != ans) {
				okay = false;
			}
			break;

		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main()
{
	clock_t start = clock();
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int TC, MARK;
	scanf("%d %d", &TC, &MARK);

	//TC = 1;
	for (int tc = 1; tc <= TC; ++tc)
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