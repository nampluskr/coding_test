// STL 1601 ms
#if 1

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAXL	(10)
#define DEFAULT	0
#define LEFT	1

struct Card {
	int cID;					// [입력]
	string word;				// [입력]
	string subject;				// [입력]

	int playerCnt;				// 카드를 보유한 플레이어의 수
	int numCards_submitted;		// 해당 라운드 (제출된 카드수)
};

struct PairHash {
	size_t operator()(const pair<string, string>& key) const {
		return hash<string>()(key.first) ^ hash<string>()(key.second);
	}
};

struct Data {
	int cID;
	int playerCnt;
	string word;

	bool operator<(const Data& card) const {
		return (this->playerCnt < card.playerCnt) ||
			(this->playerCnt == card.playerCnt && this->word > card.word);
	}
};

struct Player {
	int pID;							// [입력]
	int score;							// 초기값 0
	unordered_map<int, int> numCards;	// 입력 (cID, qty) join()
	int state;							// 초기값 DEFAULT
	int card_submitted;					// 해당 라운드 (플레이어가 제출한 카드 ID)

	//unordered_map<pair<string, string>, vector<int>, PairHash> cardMap;
	//unordered_map<pair<string, string>, priority_queue<Data>, PairHash> cardPQ;
};

unordered_map<pair<string, string>, vector<int>, PairHash> cardMap;
priority_queue<Data> cardPQ;

vector<Card> cards;
vector<Player> players;

////////////////////////////////////////////////////////////////////
void init(int N, char mWordList[][MAXL + 1], char mSubjectList[][MAXL + 1])
{
	cards.clear();
	cards.resize(N + 1);

	for (int i = 0; i < N; i++) {
		int cID = i + 1;
		cards[cID].cID = cID;
		cards[cID].word = string(mWordList[i]);
		cards[cID].subject = string(mSubjectList[i]);
	}

	players.clear();
	players.push_back({});	// players[0]

	cardMap.clear();
	while (!cardPQ.empty())
		cardPQ.pop();
}

// 데이터 입력
// mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.
void join(int mID, int M, int mCardList[])
{
	players.push_back({});
	players[mID].pID = mID;

	for (int i = 0; i < M; i++) {
		int cID = mCardList[i];

		players[mID].numCards[cID] += 1;
		if (players[mID].numCards[cID] == 1)	// 0 -> 1 일 때 카운트
			cards[cID].playerCnt += 1;

		cardMap[{cards[cID].subject, cards[cID].word.substr(0, 1)}].push_back(cID);
		cardMap[{cards[cID].subject, cards[cID].word.substr(0, 2)}].push_back(cID);
	}
}

int playRound(char mBeginStr[], char mSubject[])
{
	// 매 라운드마다 제출한 카드 개수 초기화
	for (auto& card : cards)
		card.numCards_submitted = 0;

	for (auto& player : players)
		player.card_submitted = -1;

	// 플레이어 마다 카드 제출
	int len = strlen(mBeginStr);
	auto& cardList = cardMap[{string(mSubject), string(mBeginStr).substr(0, len)}];

	while (cardPQ.size() > 0) {
		cardPQ.pop();
	}

	for (auto& cID : cardList) {
		if (cards[cID].playerCnt == 0)
			continue;
		cardPQ.push({ cID, cards[cID].playerCnt, cards[cID].word });
	}

	while (!cardPQ.empty()) {
		auto card = cardPQ.top(); cardPQ.pop();

		for (auto& player : players) {
			if (player.state == LEFT) continue;
			if (player.card_submitted != -1) continue;
			if (player.numCards[card.cID] == 0) continue;

			player.card_submitted = card.cID;
			cards[card.cID].numCards_submitted += 1;
		}
	}

	// 플레이어 점수 계산
	int sumCardIDs = 0;
	for (auto& player : players) {
		if (player.state == LEFT)
			continue;

		int cID = player.card_submitted;
		if (cID == -1)
			continue;

		sumCardIDs += cID;
		player.numCards[cID] -= 1;
		if (player.numCards[cID] == 0)
			cards[cID].playerCnt -= 1;

		int n = cards[cID].numCards_submitted - 1;
		player.score += n * n;
	}
	return sumCardIDs;
}

// 데이터 수정/조회
int leave(int mID)
{
	players[mID].state = LEFT;

	// 플레이어가 가지고 있는 모든 카드들을 반납한다. (부분 탐색)
	for (const auto& card : players[mID].numCards) {
		int cID = card.first;
		if (players[mID].numCards[cID] > 0) {
			cards[cID].playerCnt -= 1;
		}
	}

	return players[mID].score;
}
#endif