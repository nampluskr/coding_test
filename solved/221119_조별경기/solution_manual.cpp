#if 1
// Manual 497 ms
// 1.Array + 2.Linked List
#define NUM_PLAYERS 100001

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

struct LinkedList {
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;

    void clear() { head = nullptr; tail = nullptr; size = 0; }
    void push_back(int value) {
        Node* node = new Node({ value, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node;  tail = node; }
        size += 1;
    }
};

struct Player {
    int score;
    int teamIdx;
};

struct Team {
    int score;
    LinkedList playerList;
};

Player players[NUM_PLAYERS];
Team teams[NUM_PLAYERS];
int playerCnt;

///////////////////////////////////////////////////////////////////////////////
// 각 선수들은 서로 다른 ID를 가지며 ID는 1에서 N까지의 수 중 하나이다.
void init(int N)
{
    playerCnt = 0;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i] = {};
        teams[i].score = 0;
        teams[i].playerList.clear();
    }

    for (int i = 1; i <= N; i++) {
        players[i].teamIdx = i;
        teams[i].playerList.push_back(i);
    }
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
    int teamA = players[mWinnerID].teamIdx;
    int teamB = players[mLoserID].teamIdx;

    teams[teamA].score += mScore;
    teams[teamB].score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
    int teamA = players[mPlayerA].teamIdx;
    int teamB = players[mPlayerB].teamIdx;

    if (teams[teamA].playerList.size < teams[teamB].playerList.size) {
        swap(teamA, teamB);
    }
    for (auto node = teams[teamB].playerList.head; node; node = node->next) {
        int playerB = node->value;
        players[playerB].score += teams[teamB].score - teams[teamA].score;
        players[playerB].teamIdx = teamA;
        teams[teamA].playerList.push_back(playerB);
    }
    teams[teamB].playerList.clear();
}

int getScore(int mID)
{
    int ret = teams[players[mID].teamIdx].score + players[mID].score;
    return ret;
}
#endif