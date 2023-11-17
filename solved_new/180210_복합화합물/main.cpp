#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 5000
#define MAX_M 5
#define MAX_R 500

typedef struct {
    char first[11];
    char second[11];
    char third[11];
    char fourth[11];
    char fifth[11];
}INFO;

////////////////////////////////////////////////////////////////////////////////

static int Weight;

extern void init();
extern void addDB(INFO info);
extern int newCompound(INFO info);

int calc_correlation(const char str1[11], const char str2[11])
{
    int sum = 0;
    if (strcmp(str1, str2) == 0) return 100;
    else {
        for (int i = 0; i < 10; ++i) {
            if (str1[i] == 0 || str2[i] == 0) break;
            sum += ((26 - abs(str1[i] - str2[i])) * Weight);
        }
    }
    sum /= 100;
    if (sum > 99) sum = 99;
    return sum;
}

////////////////////////////////////////////////////////////////////////////////

static int N, K, R[MAX_M];
static char String[MAX_M][MAX_R][11];
static int Compound[MAX_N * 2][MAX_M];

static int seed;
static int pseudo_rand() {
    seed = seed * 214013 + 2531011;
    return (seed >> 16) & 0x7fff;
}

static void make_compound()
{
    for (int i = 0; i < MAX_M; ++i) {
        for (int k = 0; k < R[i]; ++k) {
            int length = pseudo_rand() % 6 + 5;
            for (int m = 0; m < length; ++m) {
                String[i][k][m] = 'a' + pseudo_rand() % 26;
            }
            String[i][k][length] = 0;
        }
    }

    for (int i = 0; i < (N + K); ++i) {
        for (int k = 0; k < MAX_M; ++k) {
            Compound[i][k] = pseudo_rand() % R[k];
        }
    }
}

static int run()
{
    int score = 100;

    scanf("%d %d %d %d", &N, &K, &seed, &Weight);
    scanf("%d %d %d %d %d", &R[0], &R[1], &R[2], &R[3], &R[4]);

    make_compound();

    init();

    for (int i = 0; i < N; ++i) {
        INFO info;
        strcpy(info.first, String[0][Compound[i][0]]);
        strcpy(info.second, String[1][Compound[i][1]]);
        strcpy(info.third, String[2][Compound[i][2]]);
        strcpy(info.fourth, String[3][Compound[i][3]]);
        strcpy(info.fifth, String[4][Compound[i][4]]);
        addDB(info);
    }

    for (int i = N; i < (N + K); ++i) {
        int answer;
        scanf("%d", &answer);

        INFO info;
        strcpy(info.first, String[0][Compound[i][0]]);
        strcpy(info.second, String[1][Compound[i][1]]);
        strcpy(info.third, String[2][Compound[i][2]]);
        strcpy(info.fourth, String[3][Compound[i][3]]);
        strcpy(info.fifth, String[4][Compound[i][4]]);

        int result = newCompound(info);
        if (result != answer) {
            score = 0;
        }
    }

    return score;
}

int main()
{
    clock_t start = clock();

    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    //T = 5;
    for (int tc = 1; tc <= T; tc++)
    {
        clock_t tc_start = clock();
        int score = run();
        int tc_result = (clock() - tc_start) / (CLOCKS_PER_SEC / 1000);
        printf("#%2d %d (%3d ms)\n", tc, score, tc_result);
    }
    int result = (clock() - start) / (CLOCKS_PER_SEC / 1000);
    printf(">> Result: %d ms\n", result);

    return 0;
}