#if 1
// STL 607 ms (ref.)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_LEN     (11 + 1)
#define MAX_ROOMS   (30000 + 1)   // mID 처음 호출시 1

struct Room {
    char mWord[MAX_LEN];
    char dir[3][MAX_LEN];
};
Room rooms[MAX_ROOMS];
unordered_map<string, int> roomMap;
int roomCnt;

int currentRoom;

struct Data {
    int mID;
    char mWord[MAX_LEN];

    //Data() { this->mID = 0;  strcpy_s(this->mWord, ""); }
    Data(int mID, const char mWord[]) {
        this->mID = mID;  strcpy_s(this->mWord, mWord);
    }
    bool operator<(const Data& data) const { 
        return strcmp(mWord, data.mWord) > 0;
    }
};
unordered_map<string, priority_queue<Data>> roomPQMap[3];

/////////////////////////////////////////////////////////////////////
void init()
{
    for (int i = 0; i < MAX_ROOMS; i++) { rooms[i] = {}; }
    roomMap.clear();
    roomCnt = 0;

    for (int i = 0; i < 3; i++)
        roomPQMap[i].clear();
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    strcpy_s(rooms[mID].mWord, mWord);
    strncpy_s(rooms[mID].dir[0], mWord, mDirLen[0]);
    strncpy_s(rooms[mID].dir[1], mWord + 4, mDirLen[1]);
    strncpy_s(rooms[mID].dir[2], mWord + 11 - mDirLen[2], mDirLen[2]);

    string word = string(mWord);
    roomMap.emplace(word, mID);
    roomPQMap[0][word.substr(7, 4)].push({ mID, mWord });
    roomPQMap[0][word.substr(9, 2)].push({ mID, mWord });
    roomPQMap[1][word.substr(4, 3)].push({ mID, mWord });
    roomPQMap[2][word.substr(0, 4)].push({ mID, mWord });
    roomPQMap[2][word.substr(0, 2)].push({ mID, mWord });
}

void setCurrent(char mWord[])
{
    int mID = roomMap[string(mWord)];
    currentRoom = mID;
}

int moveDir(int mDir)
{
    int ret = 0;
    string subWord = string(rooms[currentRoom].dir[mDir]);
    auto& Q = roomPQMap[mDir][subWord];

    vector<int> popped;
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (strcmp(rooms[data.mID].mWord, data.mWord) != 0) continue;
        
        popped.push_back(data.mID);
        if (data.mID != currentRoom) {
            ret = data.mID;
            break;
        }
    }
    for (int mID : popped) { Q.push({ mID, rooms[mID].mWord}); }
    if (ret != 0) { currentRoom = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[string(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}
#endif