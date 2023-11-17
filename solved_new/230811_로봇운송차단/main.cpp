#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#define MAX_N 20

extern void init(int N, int mMap[MAX_N][MAX_N]);
extern int numberOfCandidate(int M, int mStructure[]);
extern int maxBlockedRobots(int M, int mStructure[], int mDir);

#define CMD_INIT 100
#define CMD_CANDI 200
#define CMD_BLOCKED 300

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int N;
            int mMap[MAX_N][MAX_N];
            scanf("%d", &N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    scanf("%d", &mMap[i][j]);
                }
            }
            init(N, mMap);
            ok = true;
        }
        else if (query == CMD_CANDI)
        {
            int M;
            int mStructure[5];

            scanf("%d", &M);
            for (int i = 0; i < M; i++) {
                scanf("%d", &mStructure[i]);
            }
            int ret = numberOfCandidate(M, mStructure);

            scanf("%d", &ans);
            if (ans != ret) {
                ok = false;
            }
        }
        else if (query == CMD_BLOCKED)
        {
            int M;
            int mStructure[5];
            int mDir;

            scanf("%d", &M);
            for (int i = 0; i < M; i++) {
                scanf("%d", &mStructure[i]);
            }

            scanf("%d", &mDir);
            int ret = maxBlockedRobots(M, mStructure, mDir);
            scanf("%d", &ans);
            if (ans != ret) {
                ok = false;
            }
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
    scanf("%d %d", &T, &MARK);

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