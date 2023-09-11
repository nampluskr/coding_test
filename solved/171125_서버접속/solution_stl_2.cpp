#if 0
// (TC = 5) STL-2 61 ms / STL-1 88 ms / Brute force 646 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define NUM_ACCOUNTS    50000
#define MAX_LENGTH      11
#define LOGOUT          1

struct Account {
    char password[MAX_LENGTH];
    int default_time;
    int logout_time;
    int state;
};
vector<Account> accounts;
int accountCnt;

unordered_map<string, int> accountMap;
int current_time;

struct Data {
    int aIdx;
    int logout_time;
    bool operator<(const Data& data) const { return logout_time > data.logout_time; }
};
priority_queue<Data> logoutAccPQ;

//////////////////////////////////////////////////////////////////////////////
int get_accountIndex(const char id[]) {
    int aIdx;
    auto ret = accountMap.find(string(id));
    if (ret == accountMap.end()) {
        aIdx = accountCnt;
        accountMap.emplace(string(id), aIdx);
        accountCnt += 1;
    }
    else { aIdx = ret->second; }
    return aIdx;
}

//////////////////////////////////////////////////////////////////////////////
void Init()
{
    accounts.clear();   accounts.resize(NUM_ACCOUNTS);
    accountCnt = 0;
    accountMap.clear();
    current_time = 0;

    while (!logoutAccPQ.empty()) { logoutAccPQ.pop(); }
}

void NewAccount(char id[], char password[], int defaulttime)
{
    int aIdx = get_accountIndex(id);
    strcpy(accounts[aIdx].password, password);
    accounts[aIdx].default_time = defaulttime;

    int logout_time = current_time + defaulttime;
    accounts[aIdx].logout_time = logout_time;
    logoutAccPQ.push({ aIdx, logout_time });
}

void Logout(char id[])
{
    int aIdx = get_accountIndex(id);
    accounts[aIdx].state = LOGOUT;
}

void Connect(char id[], char password[])
{
    int aIdx = get_accountIndex(id);
    if (strcmp(accounts[aIdx].password, password) != 0) return;
    if (accounts[aIdx].state == LOGOUT) return;

    int logout_time = current_time + accounts[aIdx].default_time;
    accounts[aIdx].logout_time = logout_time;
    logoutAccPQ.push({ aIdx, logout_time });
}

int Tick()
{
    current_time += 1;

    int ret = 0;
    auto& Q = logoutAccPQ;

    while (!Q.empty() && Q.top().logout_time <= current_time) {
        auto data = Q.top(); Q.pop();
        int aIdx = data.aIdx;

        if (accounts[aIdx].logout_time != current_time) continue;

        if (accounts[aIdx].state != LOGOUT) {
            accounts[aIdx].state = LOGOUT;
            ret += 1;
        }
    }
    return ret;
}
#endif