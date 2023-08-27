#if 0
// Bruet force 2168 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

#define NUM_USERS   500000
#define LOGIN   0
#define LOGOUT  1

struct User {
    char id[11];
    char password[11];
    int default_time;

    int login_time;
    int state;
};
vector<User> users;
int userCnt;

unordered_map<string, int> userMap;

//////////////////////////////////////////////////////////////////////////////
int get_userIndex(const char id[]) {
    int uIdx;
    auto ptr = userMap.find(string(id));
    if (ptr == userMap.end()) {
        uIdx = userCnt;
        userMap.emplace(string(id), uIdx);
        userCnt += 1;
    }
    else { uIdx = ptr->second; }
    return uIdx;
}

//////////////////////////////////////////////////////////////////////////////
void Init()
{
    users.clear();  users.resize(NUM_USERS);
    userCnt = 0;
    userMap.clear();
}

void NewAccount(char id[11], char password[11], int defaulttime) {
    int uIdx = get_userIndex(id);
    strcpy(users[uIdx].id, id);
    strcpy(users[uIdx].password, password);
    users[uIdx].default_time = defaulttime;
    users[uIdx].login_time = defaulttime;
    users[uIdx].state = LOGIN;
}

void Logout(char id[11]) {
    int uIdx = get_userIndex(id);
    if (users[uIdx].state == LOGIN) {
        users[uIdx].state = LOGOUT;
    }
}

void Connect(char id[11], char password[11])
{
    int uIdx = get_userIndex(id);
    //if (strcmp(users[uIdx].id, id) != 0) return;
    if (strcmp(users[uIdx].password, password) != 0) return;
    if (users[uIdx].state == LOGIN) {
        users[uIdx].login_time = users[uIdx].default_time;
    }
}

int Tick()
{ 
    int ret = 0;
    for (int i = 0; i < userCnt; i++) {
        if (users[i].state != LOGOUT) {
            users[i].login_time -= 1;

            if (users[i].login_time == 0) {
                users[i].state = LOGOUT;
                ret += 1;
            }
        }
    }
    return ret;
}
#endif