#if 0
// STL xxx ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <unordered_map>
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

unordered_map<string, vector<int>> dbMap[5];

//////////////////////////////////////////////////////////////////////////////
int get_score(const INFO& info1, const INFO& info2) {
    int ret = 0;
    int score1 = calc_correlation(info1.first, info2.first);
    int score2 = calc_correlation(info1.second, info2.second);
    int score3 = calc_correlation(info1.third, info2.third);
    int score4 = calc_correlation(info1.fourth, info2.fourth);
    int score5 = calc_correlation(info1.fifth, info2.fifth);

    if (score1 == 100 || score2 == 100 || score3 == 100 || score4 == 100 || score5 == 100) {
        ret = score1 + score2 + score3 + score4 + score5;
    }
    return ret;
}

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

    dbMap[0][string(info.first)].push_back(cIdx);
    dbMap[1][string(info.second)].push_back(cIdx);
    dbMap[2][string(info.third)].push_back(cIdx);
    dbMap[3][string(info.fourth)].push_back(cIdx);
    dbMap[4][string(info.fifth)].push_back(cIdx);
}

// 5,000 x 5,000 x 5
int newCompound(INFO info)
{
    int ret = 0;
    for (int cIdx: dbMap[0][string(info.first)]) {
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (int cIdx : dbMap[1][string(info.second)]) {
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (int cIdx : dbMap[2][string(info.third)]) {
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (int cIdx : dbMap[3][string(info.fourth)]) {
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (int cIdx : dbMap[4][string(info.fifth)]) {
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    return ret;
}
#endif