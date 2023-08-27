#if 0
// [TC = 50] Manual 2812 ms / STL 2628 ms / Brue force 160,544 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>

#define NUM_COMPOUNDS   (5000)

struct INFO {
    char first[11];
    char second[11];
    char third[11];
    char fourth[11];
    char fifth[11];
};

extern int calc_correlation(const char str1[11], const char str2[11]);
int max(int a, int b) { return (a > b) ? a : b; }

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

#define MAX_TABLE 70007

unsigned long hashfunc(const char str[]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

LinkedList<int> dbMap1[MAX_TABLE];
LinkedList<int> dbMap2[MAX_TABLE];
LinkedList<int> dbMap3[MAX_TABLE];
LinkedList<int> dbMap4[MAX_TABLE];
LinkedList<int> dbMap5[MAX_TABLE];

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

    int hashkey1 = hashfunc(info.first);
    dbMap1[hashkey1].push_back(cIdx);

    int hashkey2 = hashfunc(info.second);
    dbMap2[hashkey2].push_back(cIdx);

    int hashkey3 = hashfunc(info.third);
    dbMap3[hashkey3].push_back(cIdx);

    int hashkey4 = hashfunc(info.fourth);
    dbMap4[hashkey4].push_back(cIdx);

    int hashkey5 = hashfunc(info.fifth);
    dbMap5[hashkey5].push_back(cIdx);
}

// 5,000 x 5,00 x 5
int newCompound(INFO info)
{
    int ret = 0;
    int hashkey1 = hashfunc(info.first);
    for (auto ptr = dbMap1[hashkey1].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    int hashkey2 = hashfunc(info.second);
    for (auto ptr = dbMap2[hashkey2].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    int hashkey3 = hashfunc(info.third);
    for (auto ptr = dbMap3[hashkey3].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    int hashkey4 = hashfunc(info.fourth);
    for (auto ptr = dbMap4[hashkey4].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    int hashkey5 = hashfunc(info.fifth);
    for (auto ptr = dbMap5[hashkey5].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int socre = get_score(db[cIdx].info, info);
        ret = max(ret, socre);
    }
    return ret;
}
#endif