#if 0
// (TC = 5) Brute force 646 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>
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
}

void NewAccount(char id[], char password[], int defaulttime)
{
    int aIdx = get_accountIndex(id);
    strcpy(accounts[aIdx].password, password);
    accounts[aIdx].default_time = defaulttime;
    accounts[aIdx].logout_time = current_time + defaulttime;
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

    accounts[aIdx].logout_time = current_time + accounts[aIdx].default_time;
}

int Tick()
{
    current_time += 1;

    int ret = 0;
    for (int i = 0; i < accountCnt; i++) {
        if (accounts[i].logout_time != current_time) continue;

        if (accounts[i].state != LOGOUT) {
            accounts[i].state = LOGOUT;
            ret += 1;
        }

    }
    return ret;
}
#endif