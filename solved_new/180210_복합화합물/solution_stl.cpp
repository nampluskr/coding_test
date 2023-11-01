#if 0
// STL 2625 ms (TC = 50)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;

#define MAX_COMPOUNDS   (5000 + 1)

typedef struct {
    char first[11];
    char second[11];
    char third[11];
    char fourth[11];
    char fifth[11];
}INFO;

extern int calc_correlation(const char str1[11], const char str2[11]);


struct Compound {
    INFO info;
};
vector<Compound> compounds;
int compoundCnt;

unordered_map<string, vector<int>> firstMap;
unordered_map<string, vector<int>> secondMap;
unordered_map<string, vector<int>> thirdMap;
unordered_map<string, vector<int>> fourthMap;
unordered_map<string, vector<int>> fifthMap;

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
void init()
{
    compounds.clear();  compounds.resize(MAX_COMPOUNDS);
    compoundCnt = 0;

    firstMap.clear();
    secondMap.clear();
    thirdMap.clear();
    fourthMap.clear();
    fifthMap.clear();
}

void addDB(INFO info)
{
    int cIdx = compoundCnt++;
    strcpy(compounds[cIdx].info.first, info.first);
    strcpy(compounds[cIdx].info.second, info.second);
    strcpy(compounds[cIdx].info.third, info.third);
    strcpy(compounds[cIdx].info.fourth, info.fourth);
    strcpy(compounds[cIdx].info.fifth, info.fifth);

    firstMap[string(info.first)].push_back(cIdx);
    secondMap[string(info.second)].push_back(cIdx);
    thirdMap[string(info.third)].push_back(cIdx);
    fourthMap[string(info.fourth)].push_back(cIdx);
    fifthMap[string(info.fifth)].push_back(cIdx);
}

int newCompound(INFO info)
{
    int ret = 0;

    for (int cIdx : firstMap[string(info.first)]) {
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (int cIdx : secondMap[string(info.second)]) {
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (int cIdx : thirdMap[string(info.third)]) {
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (int cIdx : fourthMap[string(info.fourth)]) {
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (int cIdx : fifthMap[string(info.fifth)]) {
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    return ret;
}
#endif