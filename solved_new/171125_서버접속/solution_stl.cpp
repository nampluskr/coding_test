#if 1
// STL 78 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
using namespace std;

#define MAX_LEN     (10 + 1)
#define MAX_USERS   (50000 + 1)
#define MAX_TIME    (50000 + 1)
#define LOGOUT      1

struct User {
    char password[MAX_LEN];
    int defaultTime;
    int logoutTime;
    int state;
};
User users[MAX_USERS];
int userCnt;
unordered_map<string, int> userMap;

int currentTime;
vector<int> logoutUserList[MAX_TIME];

////////////////////////////////////////////////////////////////////
int get_userIndex(const char id[]) {
    int uIdx;
    auto ptr = userMap.find(string(id));
    if (ptr == userMap.end()) {
        uIdx = userCnt++;
        userMap.emplace(string(id), uIdx);
    }
    else { uIdx = ptr->second; }
    return uIdx;
}

////////////////////////////////////////////////////////////////////
void Init() {
    for (int i = 0; i < MAX_USERS; i++) { users[i] = {}; }
    userCnt = 0;
    userMap.clear();

    currentTime = 0;
    for (int i = 0; i < MAX_TIME; i++) { logoutUserList[i].clear(); }
}

void NewAccount(char id[11], char password[11], int defaulttime) {
    int uIdx = get_userIndex(id);
    
    strcpy(users[uIdx].password, password);
    users[uIdx].defaultTime = defaulttime;
    users[uIdx].logoutTime = currentTime + defaulttime;

    logoutUserList[users[uIdx].logoutTime].push_back(uIdx);
}

void Logout(char id[11]) {
    int uIdx = get_userIndex(id);
    
    if (users[uIdx].state != LOGOUT) {
        users[uIdx].state = LOGOUT;
    }
}

void Connect(char id[11], char password[11]) {
    int uIdx = get_userIndex(id);
    
    if (strcmp(users[uIdx].password, password) != 0) { return; }
    if (users[uIdx].state != LOGOUT) {
        users[uIdx].logoutTime = currentTime + users[uIdx].defaultTime;
        logoutUserList[users[uIdx].logoutTime].push_back(uIdx);
    }
}

int Tick() {
    currentTime += 1;
    int ret = 0;

    for (int uIdx: logoutUserList[currentTime]) {
        if (users[uIdx].state == LOGOUT) continue;

        if (users[uIdx].logoutTime == currentTime) {
            users[uIdx].state = LOGOUT;
            ret += 1;
        }
    }
    return ret;
}
#endif