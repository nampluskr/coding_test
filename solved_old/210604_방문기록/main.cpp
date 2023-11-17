#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

#define MAX_N (10000)
#define MAX_M (10)

extern void init(int, int, int, int[]);
extern void visit(int, int);
extern int getNewestVisited(int, int[]);
extern int getOldestVisited(int, int[]);
extern void getMostVisited(int, int[]);
extern void getMostVisitedAll(int[]);

const int COM_VISIT = 200;
const int COM_NEW = 300;
const int COM_OLD = 400;
const int COM_MOST = 500;
const int COM_MOST_ALL = 600;

static int n, m, k;
static int uid_list[MAX_N + 5];

static int run(int score)
{
    int query_cnt;
    scanf("%d", &query_cnt);

    for (int q = 0; q < query_cnt; q++)
    {
        int command, uid, pid;
        int user_ans, user_ans_list[MAX_M], correct_ans, correct_ans_list[MAX_M];

        scanf("%d", &command);

        if (command == COM_VISIT)
        {
            scanf("%d%d", &uid, &pid);
            visit(uid, pid);

            continue;
        }
        else if (command == COM_NEW || command == COM_OLD || command == COM_MOST)
        {
            scanf("%d", &uid);
            if (command == COM_NEW)
            {
                user_ans = getNewestVisited(uid, user_ans_list);
                scanf("%d", &correct_ans);
            }
            else if (command == COM_OLD)
            {
                user_ans = getOldestVisited(uid, user_ans_list);
                scanf("%d", &correct_ans);
            }
            else if (command == COM_MOST)
            {
                correct_ans = user_ans = m;
                getMostVisited(uid, user_ans_list);
            }
        }
        else
        {
            correct_ans = user_ans = m;
            getMostVisitedAll(user_ans_list);
        }

        if (user_ans != correct_ans)
            score = 0;

        for (int i = 0; i < correct_ans; i++)
        {
            scanf("%d", correct_ans_list + i);

            if (correct_ans_list[i] != user_ans_list[i])
            {
                score = 0;
            }
        }
    }

    return score;
}

int main()
{
    clock_t start = clock();

    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int TC, score;
    scanf("%d%d", &TC, &score);

    for (int t = 1; t <= TC; t++)
    {
        clock_t tc_start = clock();
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", uid_list + i);
        }
        init(n, m, k, uid_list);
        int user_score = run(score);
        int tc_result = (clock() - tc_start) / (CLOCKS_PER_SEC / 1000);
        printf("#%2d %d (%3d ms)\n", t, user_score, tc_result);
    }
    int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf(">> Result: %d ms\n", result);
    return 0;
}