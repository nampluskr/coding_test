#if 0
// [TC = 50]  Brue force 160,544 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
using namespace std;

#define NUM_COMPOUNDS   (5000)

struct INFO {
    char first[11];
    char second[11];
    char third[11];
    char fourth[11];
    char fifth[11];
};

extern int calc_correlation(const char str1[11], const char str2[11]);

struct Compound {
    INFO info;
};
vector<Compound> db;
int dbCnt;

//////////////////////////////////////////////////////////////////////////////
void init()
{
    db.clear();  db.resize(NUM_COMPOUNDS);
    dbCnt = 0;
}

// 5,000
void addDB(INFO info)
{
    int cIdx = dbCnt++;
    strcpy(db[cIdx].info.first, info.first);
    strcpy(db[cIdx].info.second, info.second);
    strcpy(db[cIdx].info.third, info.third);
    strcpy(db[cIdx].info.fourth, info.fourth);
    strcpy(db[cIdx].info.fifth, info.fifth);
}

// 5,000 x 5,000 x 5
int newCompound(INFO info)
{
    int ret = 0;

    for (int i = 0; i < dbCnt; i++) {
        int score1 = calc_correlation(db[i].info.first, info.first);
        int score2 = calc_correlation(db[i].info.second, info.second);
        int score3 = calc_correlation(db[i].info.third, info.third);
        int score4 = calc_correlation(db[i].info.fourth, info.fourth);
        int score5 = calc_correlation(db[i].info.fifth, info.fifth);

        if (score1 == 100 || score2 == 100 || score3 == 100 || score4 == 100 || score5 == 100) {
            ret = max(ret, score1 + score2 + score3 + score4 + score5);
        }
    }
    return ret;
}
#endif