# 171125_서버접속

## 자료구조

```cpp
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

// STL-1
unordered_map<int, vector<int>> logoutAccList;

// STL-2
struct Data {
    int aIdx;
    int logout_time;
    bool operator<(const Data& data) const {
        return logout_time > data.logout_time;
    }
};
priority_queue<Data> logoutAccPQ;
```

```cpp
int get_accountIndex(const char id[]) {}
```

## User Code

```cpp
void init()
```

```cpp
void NewAccount(char id[], char password[], int defaulttime)
```
- 새로운 사용자 계정을 추가한다.
- 해당 계정은 자동으로 login 되며, 접속시간은 defaulttime 으로 초기화된다.

```cpp
void Logout(char id[])
```
- id 에 해당 하는 계정의 서버 접속을 종료한다.
- 서버에 login 되어 있지 않는 계정은 아무런 동작도 하지 않는다.

```cpp
void Connect(char id[], char password[])
```
- 서버에 login 되어 있는 계정 중에서 id, password 가 일치하는 계정의 접속시간이 defaulttime 값으로 초기화된다.
- 서버에 login 되어 있지 않는 계정은 아무런 동작도 하지 않는다.

```cpp
int Tick()
```
- login 되어 있는 모든 계정의 접속시간이 1 감소되며, 접속시간이 0 이 되는 계정은 자동으로 logout 된다.
- 접속시간이 0 이 되어 자동으로 logout 되는 계정의 수를 리턴한다.