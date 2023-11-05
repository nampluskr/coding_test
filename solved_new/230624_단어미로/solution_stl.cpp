#if 0
// STL 584 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_ROOMS   (30000 + 1)
#define MAX_LEN     (11 + 1)

struct Room {
    char mWord[MAX_LEN];
    char mDirWord[3][4 + 1];
};
//vector<Room> rooms;
Room rooms[MAX_ROOMS];
int roomCnt;
unordered_map<string, int> roomMap;

int currentRoomID;

struct Data {
    char mWord[MAX_LEN];
    int mID;

    Data(const char mWord[], int mID) {
        strcpy(this->mWord, mWord);
        this->mID = mID;
    }
    bool operator<(const Data& data) const { return strcmp(mWord, data.mWord) > 0; }
};
unordered_map<string, priority_queue<Data>> moveDirMap[3];

////////////////////////////////////////////////////////////////////
void init()
{
    //rooms.clear();  rooms.resize(MAX_ROOMS);
    for (int i = 0; i < MAX_ROOMS; i++) { rooms[i] = {}; }
    roomCnt = 0;
    roomMap.clear();

    for (int i = 0; i < 3; i++) { moveDirMap[i].clear(); }
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    roomCnt++;
    roomMap.emplace(mWord, mID);

    strcpy(rooms[mID].mWord, mWord);
    strncpy_s(rooms[mID].mDirWord[0], mWord + 0, mDirLen[0]);
    strncpy_s(rooms[mID].mDirWord[1], mWord + 4, mDirLen[1]);
    strncpy_s(rooms[mID].mDirWord[2], mWord + 11 - mDirLen[2], mDirLen[2]);

    string word = string(mWord);
    moveDirMap[0][word.substr(9, 2)].push({ mWord, mID});
    moveDirMap[0][word.substr(7, 4)].push({ mWord, mID });
    moveDirMap[1][word.substr(4, 3)].push({ mWord, mID });
    moveDirMap[2][word.substr(0, 2)].push({ mWord, mID });
    moveDirMap[2][word.substr(0, 4)].push({ mWord, mID });
}

void setCurrent(char mWord[])
{
    int mID = roomMap[mWord];
    currentRoomID = mID;
}

int moveDir(int mDir)
{
    auto& Q = moveDirMap[mDir][rooms[currentRoomID].mDirWord[mDir]];
    vector<int> popped;
    int ret = 0;

    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (strcmp(rooms[data.mID].mWord, data.mWord) != 0) continue;

        popped.push_back(data.mID);
        if (data.mID != currentRoomID) {
            ret = data.mID;
            break;
        }
    }
    for (int mID : popped) { Q.push({ rooms[mID].mWord, mID}); }
    if (ret != 0) { currentRoomID = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[mWord];
    addRoom(mID, mChgWord, mChgLen);
} 
#endif