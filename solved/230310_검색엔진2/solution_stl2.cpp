#if 0
// STL xxx ms: ������ �߰�/������ ���� ������
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
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
	int count;				// ��ȸ��
	vector<int> wordList;	// �˻��� �ε��� ����Ʈ
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

//////////////////////////////////////////////////////
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
	priority_queue<Data> Q;

	// ������
	for (int wIdx = 0; wIdx < wordCnt; wIdx++) {
		int group = words[wIdx].group;
		if (strncmp(words[wIdx].str, prefix, strlen(prefix)) == 0)
			Q.push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
	}

	// �켱���� ���� k �� ���� (�̺���)
	vector<int> topk{};
	int cnt = 0;
	while (not Q.empty() && cnt < k) {
		Data data = Q.top(); Q.pop();

		topk.push_back(data.wIdx);
		cnt += 1;
	}
	return topk;
}

//////////////////////////////////////////////////////
void init()
{
	wordMap.clear();
	words.clear();	words.resize(NUM_WORDS);
	groups.clear();	groups.resize(NUM_WORDS);
	wordCnt = 0;

	for (int i=0; i<27; i++)
		while (!wordPQ[i].empty()) { wordPQ[i].pop(); }
}

// ������ ����: 15,000
void search(char mStr[], int mCount)
{
	int wIdx = get_wordIndex(mStr);
	groups[words[wIdx].group].count += mCount;

	//int idx = mStr[0] - 'a' + 1;
	//wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
	//wordPQ[idx].push({wIdx, words[wIdx].str, groups[words[wIdx].group].count});
}

// ������ ��ȸ: 500
Result recommend(char mStr[])
{
	Result ret = { 0, 0 };
	char prefix[MAXL];

	for (int i = 0; i <= strlen(mStr); i++) {
		strncpy(prefix, mStr, i);
		const auto& top5 = get_topk(prefix, 5);

		for (int j = 0; j < top5.size(); j++) {
			int wIdx = top5[j];
			if (strcmp(words[wIdx].str, mStr) == 0) {
				ret.mOrder = i;		// �Է��� ���� ����
				ret.mRank = j + 1;	// ��ġ�� �� ����

				// ����� ��ȯ (�˻����� ��ȸ�� 1 ����)
				groups[words[wIdx].group].count += 1;

				//int idx = words[wIdx].str[0] - 'a' + 1;
				//wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
				//wordPQ[idx].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
				return ret;
			}
		}
	}
	return ret;
}

// 50
int relate(char mStr1[], char mStr2[])
{
	int group1 = words[get_wordIndex(mStr1)].group;	// ū �׷�
	int group2 = words[get_wordIndex(mStr2)].group;	// ���� �׷�

	if (groups[group1].wordList.size() < groups[group2].wordList.size())
		swap(group1, group2);

	groups[group1].count += groups[group2].count;
	for (int word2 : groups[group2].wordList) {
		words[word2].group = group1;
		groups[group1].wordList.push_back(word2);
	}

	// pq ������Ʈ
	//for (int wIdx : groups[group1].wordList) {
	//	int idx = words[wIdx].str[0] - 'a' + 1;
	//	wordPQ[0].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
	//	wordPQ[idx].push({ wIdx, words[wIdx].str, groups[words[wIdx].group].count });
	//}
	return groups[group1].count;
}

// 6,000
void rank(char mPrefix[], int mRank, char mReturnStr[])
{
	vector<int> ret = get_topk(mPrefix, mRank);
	strcpy(mReturnStr, words[ret[mRank - 1]].str);
}
#endif