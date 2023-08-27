#if 1
// [TC = 50] Manual xxx ms / STL 2628 ms / Brue force 160,544 ms
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
Compound db[NUM_COMPOUNDS];
int dbCnt;

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

unordered_map<string, LinkedList<int>> dbMap1;
unordered_map<string, LinkedList<int>> dbMap2;
unordered_map<string, LinkedList<int>> dbMap3;
unordered_map<string, LinkedList<int>> dbMap4;
unordered_map<string, LinkedList<int>> dbMap5;

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
    for (int i = 0; i < NUM_COMPOUNDS; i++) { db[i] = {}; }
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

    dbMap1[string(info.first)].push_back(cIdx);
    dbMap2[string(info.second)].push_back(cIdx);
    dbMap3[string(info.third)].push_back(cIdx);
    dbMap4[string(info.fourth)].push_back(cIdx);
    dbMap5[string(info.fifth)].push_back(cIdx);
}

// 5,000 x 5,00 x 5
int newCompound(INFO info)
{
    int ret = 0;
    for (auto ptr = dbMap1[string(info.first)].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (auto ptr = dbMap2[string(info.second)].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (auto ptr = dbMap3[string(info.third)].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (auto ptr = dbMap4[string(info.fourth)].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    for (auto ptr = dbMap5[string(info.fifth)].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    return ret;
}
#endif