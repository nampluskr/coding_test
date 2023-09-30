#if 0
// STL 495 ms
#include <vector>
using namespace std;

struct Player {
    int score;
    int teamIdx;
};
vector<Player> players;

struct Team {
    int score;
    vector<int> playerList;
};
vector<Team> teams;

///////////////////////////////////////////////////////////////////////////////
// 각 선수들은 서로 다른 ID를 가지며 ID는 1에서 N까지의 수 중 하나이다.
void init(int N)
{
    players.clear();    players.resize(N + 1);
    teams.clear();      teams.resize(N + 1);

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

    if (teams[teamA].playerList.size() < teams[teamB].playerList.size()) {
        swap(teamA, teamB);
    }
    for (int playerB: teams[teamB].playerList) {
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