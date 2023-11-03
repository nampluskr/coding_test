#if 1
// STL 2625 ms (TC = 50), Manual 2353 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
using namespace std;

inline int max(int a, int b) { return (a < b) ? b : a; }

#define MAX_COMPOUNDS   (5000 + 1)

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

#define MAX_TABLE   5007
struct HashMapList {
    LinkedList<int> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int hashfunc(const char key[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *key++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    void emplace(const char key[], int value) {
        int hash = hashfunc(key);
        table[hash].push_back(value);
    }
    LinkedList<int>& operator[](const char key[]) {
        int hash = hashfunc(key);
        return table[hash];
    }
};

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
Compound compounds[MAX_COMPOUNDS];
int compoundCnt;

HashMapList firstMap;
HashMapList secondMap;
HashMapList thirdMap;
HashMapList fourthMap;
HashMapList fifthMap;

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
    for (int i = 0; i < MAX_COMPOUNDS; i++) { compounds[i] = {}; }
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

    firstMap.emplace(info.first, cIdx);
    secondMap.emplace(info.second, cIdx);
    thirdMap.emplace(info.third, cIdx);
    fourthMap.emplace(info.fourth, cIdx);
    fifthMap.emplace(info.fifth, cIdx);
}

int newCompound(INFO info)
{
    int ret = 0;

    for (auto ptr = firstMap[info.first].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (auto ptr = secondMap[info.second].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (auto ptr = thirdMap[info.third].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (auto ptr = fourthMap[info.fourth].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    for (auto ptr = fifthMap[info.fifth].head; ptr; ptr = ptr->next) {
        int cIdx = ptr->data;
        int score = get_score(info, compounds[cIdx].info);
        ret = max(ret, score);
    }
    return ret;
}
#endif