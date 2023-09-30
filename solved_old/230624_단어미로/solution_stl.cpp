#if 0
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define MAX_ROOMS	(30000 + 1)

struct Room {
    int mID;
    string word;
    string dir[3];
};
vector<Room> rooms;
unordered_map<string, int> roomMap;
int current_roomID;

struct Data {
    int mID;
    string word;
    bool operator<(const Data& data) const { return word > data.word; }
};
unordered_map<string, priority_queue<Data>> dirPQMap[3];

//////////////////////////////////////////////////////////////////////////////
void init()
{
    rooms.clear();	rooms.resize(MAX_ROOMS);
    roomMap.clear();

    for (int i = 0; i < 3; i++) { dirPQMap[i].clear(); }
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
    string word = string(mWord);
    rooms[mID].mID = mID;
    rooms[mID].word = word;
    rooms[mID].dir[0] = word.substr(0, mDirLen[0]);
    rooms[mID].dir[1] = word.substr(4, mDirLen[1]);
    rooms[mID].dir[2] = word.substr(11 - mDirLen[2], mDirLen[2]);

    roomMap[word] = mID;

    dirPQMap[0][word.substr(9, 2)].push({ mID, word });
    dirPQMap[0][word.substr(7, 4)].push({ mID, word });
    dirPQMap[1][word.substr(4, 3)].push({ mID, word });
    dirPQMap[2][word.substr(0, 2)].push({ mID, word });
    dirPQMap[2][word.substr(0, 4)].push({ mID, word });
}

void setCurrent(char mWord[])
{
    current_roomID = roomMap[string(mWord)];
}

int moveDir(int mDir)
{
    string subWord = rooms[current_roomID].dir[mDir];
    auto& Q = dirPQMap[mDir][subWord];

    int ret = 0;
    vector<int> popped;
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (rooms[data.mID].word != data.word) continue;

        popped.push_back(data.mID);
        if (data.mID != current_roomID) {
            ret = data.mID;
            break;
        }
    }
    for (int mID : popped) { Q.push({ mID, rooms[mID].word }); }
    if (ret != 0) { current_roomID = ret; }
    return ret;
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[string(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}
#endif
