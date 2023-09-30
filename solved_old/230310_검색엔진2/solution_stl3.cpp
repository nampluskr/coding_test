#if 1 // (미해결)
// STL xxx ms: 데이터 추가/변경시 마다 힙정렬 (첫글자 알파벳 별로 우큐 생성)
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <string.h>
using namespace std;

#define MAXL		8
#define NUM_WORDS	7000

struct Result {
    int mOrder;
    int mRank;
};

struct Word {
    char str[MAXL];
    int group;
};

struct Group {
    int count;				// 조회수
    vector<int> wordList;	// 검색어 인덱스 리스트
};

unordered_map<string, int> wordMap;
vector<Word> words;
vector<Group> groups;
int wordCnt;

struct Data {
    int wIdx;
    char str[MAXL];
    int count;

    Data(int _wIdx, char _str[], int _count) {
        wIdx = _wIdx; strcpy(str, _str); count = _count;
    }
    bool operator<(const Data& data) const {
        return (count < data.count) ||
            (count == data.count && strcmp(str, data.str) > 0);
    }
};

priority_queue<Data> wordPQ[27];

//////////////////////////////////////////////////////////////////////////////
int get_wordIndex(char mStr[]) {
    int wIdx = -1;
    auto ptr = wordMap.find(string(mStr));
    if (ptr == wordMap.end()) {
        wIdx = wordCnt;
        wordMap[string(mStr)] = wIdx;
        wordCnt += 1;

        strcpy(words[wIdx].str, mStr);
        words[wIdx].group = wIdx;
        groups[wIdx].wordList.push_back(wIdx);
    }
    else { wIdx = ptr->second; }
    return wIdx;
}

vector<int> get_topk(char prefix[], int k) {
    int idx;
    if (strlen(prefix) == 0) { idx = 0; }
    else { idx = prefix[0] - 'a' + 1; }
    priority_queue<Data>& Q = wordPQ[idx];

    // 우선순위 상위 k 개 추출 (복원)
    vector<int> popped;
    vector<int> topk; topk.resize(k);
    int cnt = 0;
    while (not Q.empty() && cnt < k) {
        Data data = Q.top(); Q.pop();
        int gIdx = words[data.wIdx].group;

        if (groups[gIdx].count != data.count) continue;
        //if (!Q.empty() && data.wIdx == Q.top().wIdx && data.count == Q.top().count) continue;

        popped.push_back(data.wIdx);
        if (strncmp(words[data.wIdx].str, prefix, strlen(prefix)) == 0) {
            //topk.push_back(data.wIdx);
            topk[cnt] = data.wIdx;
            cnt += 1;
        }
    }
    for (int wIdx : popped) {
        Q.push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
    }
    return topk;
}

//////////////////////////////////////////////////////////////////////////////
void init()
{
    wordMap.clear();
    words.clear();	words.resize(NUM_WORDS);
    groups.clear();	groups.resize(NUM_WORDS);
    wordCnt = 0;

    for (int i = 0; i < 27; i++) { while (!wordPQ[i].empty()) wordPQ[i].pop(); }
}

// 데이터 수정: 15,000
void search(char mStr[], int mCount)
{
    int _wIdx = get_wordIndex(mStr);
    groups[words[_wIdx].group].count += mCount;

    for (int wIdx : groups[words[_wIdx].group].wordList) {
        int idx = mStr[0] - 'a' + 1;
        wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
        wordPQ[idx].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
    }
}

// 데이터 조회: 500
Result recommend(char mStr[])
{
    Result ret = { 0, 0 };
    char prefix[MAXL] = "";

    for (int i = 0; i <= strlen(mStr); i++) {
        //strncpy(prefix, mStr, i);
        strcpy(prefix, string(mStr).substr(0, i).c_str());
        const auto& top5 = get_topk(prefix, 5);

        for (int j = 0; j < top5.size(); j++) {
            int wIdx = top5[j];
            if (strcmp(words[wIdx].str, mStr) == 0) {
                ret.mOrder = i;		// 입력한 문자 길이
                ret.mRank = j + 1;	// 일치할 때 순서

                // 결과값 반환 (검색어의 조회수 1 증가)
                groups[words[wIdx].group].count += 1;

                for (int wIdx : groups[words[top5[j]].group].wordList) {
                    int idx = mStr[0] - 'a' + 1;
                    wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
                    wordPQ[idx].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
                }
                return ret;
            }
        }
    }
    return ret;
}

// 50
int relate(char mStr1[], char mStr2[])
{
    int group1 = words[get_wordIndex(mStr1)].group;	// 큰 그룹
    int group2 = words[get_wordIndex(mStr2)].group;	// 작은 그룹

    if (groups[group1].wordList.size() < groups[group2].wordList.size())
        swap(group1, group2);

    groups[group1].count += groups[group2].count;
    for (int word2 : groups[group2].wordList) {
        words[word2].group = group1;
        groups[group1].wordList.push_back(word2);
    }
    for (int wIdx : groups[group1].wordList) {
        int idx = words[wIdx].str[0] - 'a' + 1;
        wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
        wordPQ[idx].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
    }
    int ret = groups[group1].count;
    return ret;
}

// 6,000
void rank(char mPrefix[], int mRank, char mReturnStr[])
{
    int k = 0;
    vector<int> ret = get_topk(mPrefix, mRank);
    strcpy(mReturnStr, words[ret[mRank - 1]].str);
}
#endif