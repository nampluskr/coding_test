#if 0
// Manual xxx ms / STL xxx ms / Brute force xxx ms
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

//////////////////////////////////////////////////////////////////////////////
struct ListNode {
    int id;
    ListNode* next;
};

#define MAX_TABLE   707
unsigned long hashfunc(const char key[]) {
    unsigned long hash = 5381;
    int c;
    while (c = *key++) {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
    return hash % MAX_TABLE;
}

ListNode* head1[MAX_TABLE];
ListNode* head2[MAX_TABLE];
ListNode* head3[MAX_TABLE];
ListNode* head4[MAX_TABLE];
ListNode* head5[MAX_TABLE];

ListNode* appendListNode(int id, ListNode* oldHead) {
    ListNode* node = new ListNode;
    node->id = id;
    node->next = oldHead;
    return node;
}


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

    for (int i = 0; i < MAX_TABLE; i++) { 
        head1[i] = nullptr;
        head2[i] = nullptr;
        head3[i] = nullptr;
        head4[i] = nullptr;
        head5[i] = nullptr;
    }
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

    int hashkey1 = hashfunc(db[cIdx].info.first);
    int hashkey2 = hashfunc(db[cIdx].info.second);
    int hashkey3 = hashfunc(db[cIdx].info.third);
    int hashkey4 = hashfunc(db[cIdx].info.fourth);
    int hashkey5 = hashfunc(db[cIdx].info.fifth);

    head1[hashkey1] = appendListNode(cIdx, head1[hashkey1]);
    head2[hashkey2] = appendListNode(cIdx, head2[hashkey2]);
    head3[hashkey3] = appendListNode(cIdx, head3[hashkey3]);
    head4[hashkey4] = appendListNode(cIdx, head4[hashkey4]);
    head5[hashkey5] = appendListNode(cIdx, head5[hashkey5]);
}

// 5,000 x 5,00 x 5
int newCompound(INFO info)
{
    int ret = 0;

    int hashkey1 = hashfunc(info.first);
    for (auto temp = head1[hashkey1]; temp; temp = temp->next) {
        int i = temp->id;
        if (strcmp(db[i].info.first, info.first) == 0) {
            int score = get_score(db[i].info, info);
            ret = max(ret, score);
        }
    }

    int hashkey2 = hashfunc(info.second);
    for (auto temp = head2[hashkey2]; temp; temp = temp->next) {
        int i = temp->id;
        if (strcmp(db[i].info.second, info.second) == 0) {
            int score = get_score(db[i].info, info);
            ret = max(ret, score);
        }
    }

    int hashkey3 = hashfunc(info.third);
    for (auto temp = head3[hashkey3]; temp; temp = temp->next) {
        int i = temp->id;
        if (strcmp(db[i].info.third, info.third) == 0) {
            int score = get_score(db[i].info, info);
            ret = max(ret, score);
        }
    }

    int hashkey4 = hashfunc(info.fourth);
    for (auto temp = head4[hashkey4]; temp; temp = temp->next) {
        int i = temp->id;
        if (strcmp(db[i].info.fourth, info.fourth) == 0) {
            int score = get_score(db[i].info, info);
            ret = max(ret, score);
        }
    }

    int hashkey5 = hashfunc(info.fifth);
    for (auto temp = head5[hashkey5]; temp; temp = temp->next) {
        int i = temp->id;
        if (strcmp(db[i].info.fifth, info.fifth) == 0) {
            int score = get_score(db[i].info, info);
            ret = max(ret, score);
        }
    }

    return ret;
}
#endif