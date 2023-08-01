#if 1
// 우선순위큐 데이터 최소화: Room -> Data
// 문자열 비교 -> 문자 배열 strcpy(), strcmp(): 680 ms
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define LEN_WORD    (11 + 1)
#define NUM_ROOMS   (30000 + 1)

struct Room {
    int mID;
    char word[LEN_WORD];
    string dir[3];      // 접두어, 가운데, 접미어
};
unordered_map<string, int> roomMap;
vector<Room> rooms;
int current_mID;

struct Data {
    int mID;
    char word[LEN_WORD];

    Data(int _mID, char _word[]) { mID = _mID; strcpy(word, _word); }
    bool operator<(const Data& data) const { return strcmp(word, data.word) > 0; }
};
unordered_map<string, priority_queue<Data>> dirMap[3];

//////////////////////////////////////////////////////////////
void init()
{
    rooms.clear(); rooms.resize(NUM_ROOMS);
    roomMap.clear();

    for (int i = 0; i < 3; i++) { dirMap[i].clear(); }
}

// 30,000
// mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.
void addRoom(int mID, char mWord[], int mDirLen[])
{
    string word = string(mWord);
    rooms[mID].mID = mID;
    strcpy(rooms[mID].word, mWord);
    rooms[mID].dir[0] = word.substr(0, mDirLen[0]);                 // 앞 방향
    rooms[mID].dir[1] = word.substr(4, mDirLen[1]);                 // 중간 방향
    rooms[mID].dir[2] = word.substr(11 - mDirLen[2], mDirLen[2]);   // 뒤 방향

    roomMap[string(mWord)] = mID;

    dirMap[0][word.substr(9, 2)].push({ mID, mWord });   // 접미어 -> 앞 방향
    dirMap[0][word.substr(7, 4)].push({ mID, mWord });   // 접미어 -> 앞 방향
    dirMap[1][word.substr(4, 3)].push({ mID, mWord });   // 가운데 -> 중간 방향
    dirMap[2][word.substr(0, 2)].push({ mID, mWord });   // 접두어 -> 뒤 방향
    dirMap[2][word.substr(0, 4)].push({ mID, mWord });   // 접두어 -> 뒤 방향
}

// 500
void setCurrent(char mWord[])
{
    current_mID = roomMap[string(mWord)];
}

// 50,000
// 사전 순으로 가장 빠른 단어가 있는 방으로 이동
int moveDir(int mDir)
{
    string word = rooms[current_mID].dir[mDir];
    auto& Q = dirMap[mDir][word];
    vector<int> popped;
    int ret = 0;

    while (!Q.empty()) {
        auto room = Q.top(); Q.pop();

        if (strcmp(rooms[room.mID].word, room.word) != 0) continue;

        popped.push_back(room.mID);
        if (room.mID != current_mID) {
            ret = room.mID;
            break;
        }
    }
    for (int mID : popped) { Q.push({mID, rooms[mID].word}); }
    if (ret != 0) { current_mID = ret; }
    return ret;
}

// 30,000
void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[string(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}
#endif