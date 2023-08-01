// STL 1742 ms: 
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define LEN_WORD    (11 + 1)
#define NUM_ROOMS   (30000 + 1)

struct Room {
    int mID;
    string word;
    string dir[3];

    bool operator<(const Room& room) const { return word > room.word; }
};
unordered_map<string, int> roomMap;
vector<Room> rooms;
int current_mID;

unordered_map<string, priority_queue<Room>> dirMap[3];

//////////////////////////////////////////////////////////////
void init()
{
    rooms.clear();  rooms.resize(NUM_ROOMS);
    roomMap.clear();

    for (int i = 0; i < 3; i++) { dirMap[i].clear(); }
}

// 30,000
// mID는 맨 처음 호출할 때 1이고 그 다음 호출할 때마다 1씩 증가한다.
void addRoom(int mID, char mWord[], int mDirLen[])
{
    string word = string(mWord);
    rooms[mID].mID = mID;
    rooms[mID].word = word;
    rooms[mID].dir[0] = word.substr(0, mDirLen[0]);                 // 앞 방향
    rooms[mID].dir[1] = word.substr(4, mDirLen[1]);                 // 중간 방향
    rooms[mID].dir[2] = word.substr(11 - mDirLen[2], mDirLen[2]);   // 뒤 방향

    roomMap[string(mWord)] = mID;

    dirMap[0][word.substr(9, 2)].push({ mID, word });
    dirMap[0][word.substr(7, 4)].push({ mID, word });
    dirMap[1][word.substr(4, 3)].push({ mID, word });
    dirMap[2][word.substr(0, 2)].push({ mID, word });
    dirMap[2][word.substr(0, 4)].push({ mID, word });
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
    priority_queue<Room>& Q = dirMap[mDir][word];
    vector<Room> popped;
    int ret = 0;

    while (!Q.empty()) {
        Room room = Q.top(); Q.pop();

        if (rooms[room.mID].word != room.word) continue;

        popped.push_back(room);
        if (room.mID != current_mID) {
            ret = room.mID;
            break;
        }
    }
    for (const auto& room : popped) { Q.push(room); }
    if (ret != 0) { current_mID = ret; }
    return ret;
}

// 30,000
void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
    int mID = roomMap[string(mWord)];
    addRoom(mID, mChgWord, mChgLen);
}