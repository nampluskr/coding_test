### [STL PQ] - 풀이중 (1 ~ 5: 0, 5 ~ 25: 100)

```cpp
#if 1
// [STL PQ] 1125 ms WS (1 ~ 5: 0, 5 ~ 25: 100)
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define MAX_PLAYERS (39990 + 1)     // players
#define MAX_LEAGUES (3999 + 1)      // leagues
#define POPPED  1

int playerCnt;
int leagueCnt;

struct Player {
    int ID;
    int mAbility;
    bool popped;        // --> league index 로 변경유무 확인할 것!!!

    bool operator<(const Player& p) const {
        return (mAbility < p.mAbility) || (mAbility == p.mAbility && ID > p.ID);
    }
};
vector<Player> players;

struct League {
    struct cmpMax {
        bool operator()(const Player& a, const Player& b) const {
            return (a.mAbility < b.mAbility) || (a.mAbility == b.mAbility && a.ID > b.ID);
        }
    };
    struct cmpMin {
        bool operator()(const Player& a, const Player& b) const {
            return (a.mAbility > b.mAbility) || (a.mAbility == b.mAbility && a.ID < b.ID);
        }
    };

    priority_queue<Player, vector<Player>, cmpMax> maxHeap;     // max
    priority_queue<Player, vector<Player>, cmpMin> minHeap;     // min

    priority_queue<Player, vector<Player>, cmpMax> leftHeap;    // x < middle
    priority_queue<Player, vector<Player>, cmpMin> rightHeap;   // x > middle
    Player middle;
    int leftSize, rightSize;

    void insert(const Player& player) {
        // 최대값, 최소값
        players[player.ID].popped = false;
        maxHeap.push(player);
        minHeap.push(player);
        
        // 중앙값
        if (maxHeap.size() == 1 && minHeap.size() == 1) { middle = player; return; }

        if (player < middle) { leftHeap.push(player); leftSize += 1; }
        else { rightHeap.push(player); rightSize += 1; }
        update();
    }
    void update() {
        // leftSize, rightSize 차이가 2일때만 ???
        if (leftSize < rightSize) {
            leftHeap.push(middle);
            middle = rightHeap.top(); rightHeap.pop();
            leftSize += 1;
            rightSize -= 1;
        }
        else if (leftSize > rightSize) {
            rightHeap.push(middle);
            middle = leftHeap.top(); leftHeap.pop();
            rightSize += 1;
            leftSize -= 1;
        }
    }
    int get_minID() {
        while (!minHeap.empty() && players[minHeap.top().ID].popped) { minHeap.pop(); }
        auto player = minHeap.top(); minHeap.pop();
        players[player.ID].popped = true;
        leftSize -= 1;
        return player.ID;
    }
    int get_maxID() {
        while (!maxHeap.empty() && players[maxHeap.top().ID].popped) { maxHeap.pop(); }
        auto player = maxHeap.top(); maxHeap.pop();
        players[player.ID].popped = true;
        rightSize -= 1;
        return player.ID;
    }
    int get_midID() {
        //while (!leftHeap.empty() && players[leftHeap.top().ID].popped) { leftHeap.pop(); }
        //while (!rightHeap.empty() && players[rightHeap.top().ID].popped) { rightHeap.pop(); }

        //while (players[middle.ID].popped) {
        //    if (leftSize < rightSize) {
        //        middle = rightHeap.top(); rightHeap.pop();
        //        rightSize -= 1;
        //    }
        //    else if (leftSize > rightSize) {
        //        middle = leftHeap.top(); leftHeap.pop();
        //        leftSize -= 1;
        //    }
        //}

        int ID = middle.ID;
        if (leftSize < rightSize) {
            middle = rightHeap.top(); rightHeap.pop();
            rightSize -= 1;
        }
        else if (leftSize > rightSize) {
            middle = leftHeap.top(); leftHeap.pop();
            leftSize -= 1;
        }
        return ID;
    }
};
vector<League> leagues;

//int minIDList[MAX_LEAGUES];
//int midIDList[MAX_LEAGUES];
//int maxIDList[MAX_LEAGUES];

/////////////////////////////////////////////////////////////////////
void init(int N, int L, int mAbility[])
{
    playerCnt = N;
    leagueCnt = L;

    players.clear();    players.resize(N);
    leagues.clear();    leagues.resize(L);

    for (int i = 0; i < playerCnt; i++) {
        players[i] = { i, mAbility[i], false };
        leagues[i / (N / L)].insert({ i, mAbility[i], false });
    }
}

// 500
int move()
{
    int ret = 0;
    vector<int> minIDList;
    vector<int> maxIDList;

    // 최대값, 최소값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int minID = leagues[i].get_minID();
        int maxID = leagues[i + 1].get_maxID();
        minIDList.push_back(minID);
        maxIDList.push_back(maxID);
        ret += minID + maxID;
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[minIDList[i]]);
    }
    return ret;
}

// 1000
int trade()
{
    int ret = 0;
    vector<int> midIDList;
    vector<int> maxIDList;

    // 중앙값, 최대값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int midID = leagues[i].get_midID();
        int maxID = leagues[i + 1].get_maxID();
        midIDList.push_back(midID);
        maxIDList.push_back(maxID);
        ret += midID + maxID;
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[midIDList[i]]);
    }
    return ret;
}
#endif
```

### [STL set-1] 

```cpp
// WS 2705 ms
#if 0
#include <vector>
#include <set>
using namespace std;

#define MAX_PLAYERS (39990 + 1)
#define MAX_LEAGUES (3999 + 1)

struct Player {
    int ID;
    int mAbility;

    bool operator<(const Player& p) const {
        return (mAbility < p.mAbility) || (mAbility == p.mAbility && ID > p.ID);
    }
};
vector<Player> players;

int playerCnt;
int leagueCnt;

struct League {
    set<Player> playerList;

    int get_midID() {
        auto mid_iter = playerList.begin();
        advance(mid_iter, playerCnt / leagueCnt / 2);
        int ID = (*mid_iter).ID;
        playerList.erase(mid_iter);
        return ID;
    }
    int get_maxID() {
        auto max_iter = playerList.end();
        max_iter--;
        int ID = (*max_iter).ID;
        playerList.erase(max_iter);
        return ID;
    }
    int get_minID() {
        auto min_iter = playerList.begin();
        int ID = (*min_iter).ID;
        playerList.erase(min_iter);
        return ID;
    }
    void insert(const Player& player) { playerList.insert(player); }
};
vector<League> leagues;

/////////////////////////////////////////////////////////////////////
void init(int N, int L, int mAbility[])
{
    playerCnt = N;
    leagueCnt = L;

    players.clear();    players.resize(N);
    leagues.clear();    leagues.resize(L);

    for (int i = 0; i < N; i++) {
        players[i].ID = i;
        players[i].mAbility = mAbility[i];
        leagues[i / (N / L)].insert(players[i]);
    }
}

int move()
{
    int ret = 0;
    vector<int> minIDList;
    vector<int> maxIDList;

    // 상위 리그 최소값과 하위 리그 최대값 찾아서 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int minID = leagues[i].get_minID();
        int maxID = leagues[i + 1].get_maxID();
        minIDList.push_back(minID);
        maxIDList.push_back(maxID);
        ret += minID + maxID;
    }
    // 상위 리그 - 하위 리그 move
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[minIDList[i]]);
    }
    return ret;
}

int trade()
{
    int ret = 0;
    vector<int> midIDList;
    vector<int> maxIDList;

    // 상위 리그 중간값과 하위 리그 최대값 찾아서 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int midID = leagues[i].get_midID();
        int maxID = leagues[i + 1].get_maxID();
        midIDList.push_back(midID);
        maxIDList.push_back(maxID);
        ret += midID + maxID;
    }
    // 상위 리그 - 하위 리그 trade
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[midIDList[i]]);
    }
    return ret;
}
#endif
```

### [STL set-2] 

```cpp
// WS vector 2705 ms / array 2776 / priority 2665
#if 0
#include <set>
using namespace std;

#define MAX_PLAYERS (39990 + 1)     // players
#define MAX_LEAGUES (3999 + 1)

struct Player {
    int ID;
    int mAbility;
};
Player players[MAX_PLAYERS];

int playerCnt;
int leagueCnt;

struct League {
    set<int> playerList;

    int get_midID() {
        auto mid_iter = playerList.begin();
        advance(mid_iter, playerCnt / leagueCnt / 2);
        int ID = *mid_iter % 100000;
        playerList.erase(mid_iter);
        return 50000 - ID;
    }
    int get_maxID() {
        auto max_iter = playerList.end();
        max_iter--;
        int ID = *max_iter % 100000;
        playerList.erase(max_iter);
        return 50000 - ID;
    }
    int get_minID() {
        auto min_iter = playerList.begin();
        int ID = *min_iter % 100000;
        playerList.erase(min_iter);
        return 50000 - ID;
    }
    void insert(const Player& player) {
        int priority = player.mAbility * 100000 + (50000 - player.ID);
        playerList.insert(priority);
    }
};
League leagues[MAX_LEAGUES];

int minIDList[MAX_LEAGUES];
int midIDList[MAX_LEAGUES];
int maxIDList[MAX_LEAGUES];

/////////////////////////////////////////////////////////////////////
void init(int N, int L, int mAbility[])
{
    playerCnt = N;
    leagueCnt = L;

    for (int i = 0; i < N; i++) { players[i] = {}; }
    for (int i = 0; i < L; i++) { leagues[i] = {}; }

    for (int i = 0; i < N; i++) {
        players[i].ID = i;
        players[i].mAbility = mAbility[i];
        leagues[i / (N / L)].insert(players[i]);
    }
}

int move()
{
    int ret = 0;

    // 상위 리그 최소값과 하위 리그 최대값 찾아서 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int minID = leagues[i].get_minID();
        int maxID = leagues[i + 1].get_maxID();
        minIDList[i] = minID;
        maxIDList[i] = maxID;
        ret += minID + maxID;
    }
    // 상위 리그 - 하위 리그 move
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[minIDList[i]]);
    }
    return ret;
}

int trade()
{
    int ret = 0;

    // 상위 리그 중간값과 하위 리그 최대값 찾아서 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int midID = leagues[i].get_midID();
        int maxID = leagues[i + 1].get_maxID();
        midIDList[i] = midID;
        maxIDList[i] = maxID;
        ret += midID + maxID;
    }
    // 상위 리그 - 하위 리그 trade
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[midIDList[i]]);
    }
    return ret;
}
#endif
```

### [STL vector] 정렬 / 추가 / 삭제

```cpp
#if 0
// [STL vector] 26245 ms WS
#include <vector>
#include <queue>
using namespace std;

#define MAX_PLAYERS (39990 + 1)     // players
#define MAX_LEAGUES (3999 + 1)      // leagues

int playerCnt;
int leagueCnt;

struct Player {
    int ID;
    int mAbility;

    bool operator<(const Player& p) const {
        return (mAbility < p.mAbility) || (mAbility == p.mAbility && ID > p.ID);
    }
};
vector<Player> players;

struct League {
    vector<Player> playerList;

    void update() {
        sort(playerList.begin(), playerList.end());
    }
    int get_midID() {
        int ID = playerList[playerCnt / leagueCnt / 2].ID;
        auto iter = playerList.begin();
        advance(iter, playerCnt / leagueCnt / 2);
        playerList.erase(iter);
        return ID;
    }
    int get_minID() { 
        int ID = playerList.front().ID;
        playerList.erase(playerList.begin());
        return ID;
    }
    int get_maxID() {
        int ID = playerList.back().ID;
        playerList.erase(--playerList.end());
        return ID;
    }
    void insert(const Player& player) { playerList.push_back(player); }
};
vector<League> leagues;

int minIDList[MAX_LEAGUES];
int midIDList[MAX_LEAGUES];
int maxIDList[MAX_LEAGUES];

/////////////////////////////////////////////////////////////////////
void init(int N, int L, int mAbility[])
{
    playerCnt = N;
    leagueCnt = L;

    players.clear();    players.resize(N);
    leagues.clear();    leagues.resize(L);

    for (int i = 0; i < playerCnt; i++) {
        players[i] = { i, mAbility[i] };
        leagues[i / (N / L)].insert({i, mAbility[i]});
    }
    for (int i = 0; i < leagueCnt; i++) { leagues[i].update(); }
}

// 500
int move()
{
    int ret = 0;

    // 최대값, 최소값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int minID = leagues[i].get_minID();
        int maxID = leagues[i + 1].get_maxID();
        minIDList[i] = minID;
        maxIDList[i] = maxID;
        ret += minID + maxID;
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[minIDList[i]]);
    }
    for (int i = 0; i < leagueCnt; i++) { leagues[i].update(); }
    return ret;
}

// 1000
int trade()
{
    int ret = 0;

    // 중앙값, 최대값 저장
    for (int i = 0; i < leagueCnt - 1; i++) {
        int midID = leagues[i].get_midID();
        int maxID = leagues[i + 1].get_maxID();
        midIDList[i] = midID;
        maxIDList[i] = maxID;
        ret += midID + maxID;
    }
    for (int i = 0; i < leagueCnt - 1; i++) {
        leagues[i].insert(players[maxIDList[i]]);
        leagues[i + 1].insert(players[midIDList[i]]);
    }
    for (int i = 0; i < leagueCnt; i++) { leagues[i].update(); }
    return ret;
}
#endif
```

### [median-1] 중앙값 만 관리

```cpp
#if 0
#include <queue>
using namespace std;

#define MAX_DB 10

struct Data {
    int value;
    bool operator<(const Data& d) const { return value < d.value; }
    bool operator>(const Data& d) const { return value > d.value; }
};
vector<Data> db;
int dbCnt;

struct Median {
    struct Greater {
        bool operator()(const Data& a, const Data& b) const { return a.value < b.value; }
    };
    struct Less {
        bool operator()(const Data& a, const Data& b) const { return a.value > b.value; }
    };
    priority_queue<Data, vector<Data>, Greater> maxHeap;    // middle 보다 작은 값
    priority_queue<Data, vector<Data>, Less> minHeap;       // middle 보다 큰 값
    Data middle;
    int heapSize;

    void clear() {
        while (!minHeap.empty()) { minHeap.pop(); }
        while (!maxHeap.empty()) { maxHeap.pop(); }
        heapSize = 0;
    }

    void push(const Data& data) {
        heapSize += 1;
        if (heapSize == 1) { middle = data; return; }

        if (data > middle) { minHeap.push({ data }); }
        else { maxHeap.push({ data }); }

        if (maxHeap.size() > minHeap.size()) {
            minHeap.push(middle);
            middle = maxHeap.top(); maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(middle);
            middle = minHeap.top(); minHeap.pop();
        }
        else { return; }
    }
    
    // 1, 3, [5], 6 -> 1, [3], 6
    // 1, [3], 5, 6 -> 1, [5], 6
    // 1, 3 [4] 5, 6 -> 1, [3], 5, 6 -> push 7: 1, [3], 5, 6, 7 -> 1, 3, [5], 6, 7
    // 1, 3 [4] 5, 6 -> 1, 3, [5], 6 -> push 7: 1, 3, [5], 6, 7 -> 1, 3, [5], 6, 7

    void pop() {
        heapSize -= 1;
        if (heapSize == 0) { return; }

        if (maxHeap.size() > minHeap.size()) {
            middle = maxHeap.top(); maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            middle = minHeap.top(); minHeap.pop();
        }
        else { middle = maxHeap.top(); maxHeap.pop(); }
    }
    Data get_median() { return middle; }
    bool empty() { return heapSize == 0; }
};
Median Q;

void init() {
    db.clear(); db.resize(MAX_DB);
    dbCnt = 0;
    Q.clear();
}

void add(int value) {
    db[dbCnt++] = { value };
    Q.push({ value });
}

void print_median() {
    while (!Q.empty()) {
        auto median = Q.get_median(); Q.pop();
        printf(">> %d\n", median.value);
    }
}


int main()
{
    init();

    // 1, 2, 3, 4, 5, 6, 7
    add(7);
    add(4);
    add(1);
    add(6);
    add(3);
    add(5);
    add(2);

    print_median();

    return 0;
}
#endif
```

### [median-2] 중앙값 + 최대값 + 최소값 관리 (풀이중)

```cpp
#if 1
#include <queue>
#include <unordered_map>
using namespace std;

#define MAX_USERS  10
#define DELETED 1

struct User {
    int userID;
    int value;
    int state;
    //bool operator<(const User& u) const { return value < u.value; }
    //bool operator>(const User& u) const { return value > u.value; }
};
vector<User> users;
int userCnt;
unordered_map<int, int> userMap;

struct Data {
    int userID;
    int value;
};

int get_userIndex(int userID) {
    int uIdx;
    auto ret = userMap.find(userID);
    if (ret == userMap.end()) {
        uIdx = userCnt++;
        userMap.emplace(userID, uIdx);
    }
    else { uIdx = ret->second; }
    return uIdx;
}

struct Median {
    struct Greater {
        bool operator()(const Data& a, const Data& b) const { return a.value < b.value; }
    };
    struct Less {
        bool operator()(const Data& a, const Data& b) const { return a.value > b.value; }
    };
    priority_queue<Data, vector<Data>, Greater> maxHeap;    // middle 보다 작은 값
    priority_queue<Data, vector<Data>, Less> minHeap;       // middle 보다 큰 값
    Data middle;
    int heapSize;

    void clear() {
        while (!minHeap.empty()) { minHeap.pop(); }
        while (!maxHeap.empty()) { maxHeap.pop(); }
        heapSize = 0;
    }
    void refresh() {
        int uIdx;
        while (!minHeap.empty()) {
            uIdx = get_userIndex(minHeap.top().userID);
            if (users[uIdx].state == DELETED) { minHeap.pop(); heapSize--; }
        }
        while (!maxHeap.empty()) { 
            uIdx = get_userIndex(minHeap.top().userID);
            if (users[uIdx].state == DELETED) { maxHeap.pop(); heapSize--; }
        }
        uIdx = get_userIndex(middle.userID);
        if (users[uIdx].state == DELETED) {
            middle = minHeap.top(); minHeap.pop();
            heapSize--;
        }
    }

    void push(const Data& data) {
        heapSize += 1;
        if (heapSize == 1) { middle = data; return; }

        if (data.value > middle.value) { minHeap.push({ data }); }
        else { maxHeap.push({ data }); }

        if (maxHeap.size() > minHeap.size()) {
            minHeap.push(middle);
            middle = maxHeap.top(); maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(middle);
            middle = minHeap.top(); minHeap.pop();
        }
        else { return; }
    }

    // 1, 3, [5], 6 -> 1, [3], 6
    // 1, [3], 5, 6 -> 1, [5], 6
    // 1, 3 [4] 5, 6 -> 1, [3], 5, 6 -> push 7: 1, [3], 5, 6, 7 -> 1, 3, [5], 6, 7
    // 1, 3 [4] 5, 6 -> 1, 3, [5], 6 -> push 7: 1, 3, [5], 6, 7 -> 1, 3, [5], 6, 7

    void pop() {
        heapSize -= 1;
        if (heapSize == 0) { return; }

        if (maxHeap.size() > minHeap.size()) {
            middle = maxHeap.top(); maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            middle = minHeap.top(); minHeap.pop();
        }
        else { middle = maxHeap.top(); maxHeap.pop(); }
    }
    Data get_median() { return middle; }
    bool empty() { return heapSize == 0; }
};
Median Q;


////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
void init() {
    users.clear(); users.resize(MAX_USERS);
    userCnt = 0;
    userMap.clear();
    Q.clear();
}

void add(int userID, int value) {
    int uIdx = get_userIndex(userID);
    users[uIdx] = { userID, value };
    Q.push({ userID, value });
}

void erase(int userID) {
    int uIdx = get_userIndex(userID);
    users[uIdx].state = DELETED;
}

void print_median() {
    while (!Q.empty()) {
        auto median = Q.get_median(); Q.pop();
        printf(">> %d\n", median.value);
    }
}


int main()
{
    init();

    // 1, 2, 3, 4, 5, 6, 7
    add(1111, 7);
    add(2222, 4);
    add(3333, 1);
    add(4444, 6);
    add(5555, 3);
    add(6666, 5);
    add(7777, 2);

    erase(2222);
    print_median();

    //erase(6666);
    //print_median();

    return 0;
}
#endif
```
