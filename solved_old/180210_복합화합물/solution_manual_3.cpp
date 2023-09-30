#if 1
// [TC = 50] Manual 2524 ms / STL 2628 ms / Brue force 160,544 ms
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

template<typename Type>
struct HashChain {
    LinkedList<Type> table[MAX_TABLE];

    unsigned long hash(const char str[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *str++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    void clear() {
        for (int i = 0; i < MAX_TABLE; i++) { table[i].clear(); }
    }
    LinkedList<Type> find(const char key[]) {
        int hashkey = hash(key);
        return table[hashkey];
    }
    void emplace(const char key[], int value) {
        int hashkey = hash(key);
        table[hashkey].push_back(value);
    }
};

HashChain<int> dbMap[5];

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
    for (int i = 0; i < 5; i++) { dbMap[i].clear(); }
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

    dbMap[0].emplace(info.first, cIdx);
    dbMap[1].emplace(info.second, cIdx);
    dbMap[2].emplace(info.third, cIdx);
    dbMap[3].emplace(info.fourth, cIdx);
    dbMap[4].emplace(info.fifth, cIdx);
}

// 5,000 x 5,00 x 5
int newCompound(INFO info)
{
    int ret = 0;
    char key[5][11];

    strcpy(key[0], info.first);
    strcpy(key[1], info.second);
    strcpy(key[2], info.third);
    strcpy(key[3], info.fourth);
    strcpy(key[4], info.fifth);

    for (int i = 0; i < 5; i++)
        for (auto ptr = dbMap[i].find(key[i]).head; ptr; ptr = ptr->next) {
            int cIdx = ptr->data;
            int socre = get_score(db[cIdx].info, info);
            ret = max(ret, socre);
        }
    return ret;
}
#endif