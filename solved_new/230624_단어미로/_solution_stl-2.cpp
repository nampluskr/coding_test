#if 0
// STL 607 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;
using ull = unsigned long long;

#define MAX_LEN     (11 + 1)
#define MAX_ROOMS   (30000 + 1)   // mID 처음 호출시 1

struct Room {
    ull word_encoded;
    int dir_encoded[3];
};
Room rooms[MAX_ROOMS];
unordered_map<ull, int> roomMap;
int roomCnt;

int currentRoom;

struct Data {
    int mID;
    ull word_encoded;

    bool operator<(const Data& data) const {
        return word_encoded > data.word_encoded;
    }
};
priority_queue<Data> roomPQMap[3][27*27*27*27];

/////////////////////////////////////////////////////////////////////
ull encode11(const char str[]) {
    ull hash = 0;
    int i = 0;
    for (; str[i]; i++) { hash = hash * 27 + str[i] - 'a' + 1; }
    for (; i < 11; i++) { hash *= 27; }
    return hash;
}

ull encode4(const char str[]) {
    ull hash = 0;
    int i = 0;
    for (; str[i]; i++) { hash = hash * 27 + str[i] - 'a' + 1; }
    for (; i < 4; i++) { hash *= 27; }
    return hash;
}

/////////////////////////////////////////////////////////////////////
void init()
{
    for (int i = 0; i < MAX_ROOMS; i++) { rooms[i] = {}; }
    roomMap.clear();
    roomCnt = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 27 * 27 * 27 * 27; j++) {
            while (!roomPQMap[i][j].empty()) { roomPQMap[i][j].pop(); }
        }
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    ull word_encoded = encode11(mWord);
    char strDir[3][5];

    strncpy_s(strDir[0], mWord + 0, mDirLen[0]);
    strncpy_s(strDir[1], mWord + 4, mDirLen[1]);
    strncpy_s(strDir[2], mWord + 11 - mDirLen[2], mDirLen[2]);

    rooms[mID].word_encoded = encode11(mWord);
    rooms[mID].dir_encoded[0] = encode4(strDir[0]);
    rooms[mID].dir_encoded[1] = encode4(strDir[1]);
    rooms[mID].dir_encoded[2] = encode4(strDir[2]);

    roomMap.emplace(word_encoded, mID);

    char str[5];
    strncpy_s(str, mWord + 7, 4);   roomPQMap[0][encode4(str)].push({ mID, word_encoded });
    strncpy_s(str, mWord + 9, 2);   roomPQMap[0][encode4(str)].push({ mID, word_encoded });
    strncpy_s(str, mWord + 4, 3);   roomPQMap[1][encode4(str)].push({ mID, word_encoded });
    strncpy_s(str, mWord + 0, 4);   roomPQMap[2][encode4(str)].push({ mID, word_encoded });
    strncpy_s(str, mWord + 0, 2);   roomPQMap[2][encode4(str)].push({ mID, word_encoded });
}

void setCurrent(char mWord[])
{
    int mID = roomMap[encode11(mWord)];
    currentRoom = mID;
}

int moveDir(int mDir)
{
    int ret = 0;
    int str_encoded = rooms[currentRoom].dir_encoded[mDir];
    auto& Q = roomPQMap[mDir][str_encoded];

    vector<int> popped;
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (rooms[data.mID].word_encoded != data.word_encoded) continue;

        popped.push_back(data.mID);
        if (data.mID != currentRoom) {
            ret = data.mID;
            break;
        }
    }
    for (int mID : popped) { Q.push({ mID, rooms[mID].word_encoded }); }
    if (ret != 0) { currentRoom = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[encode11(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}
#endif