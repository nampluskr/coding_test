# 230414_뉴스알림

## 자료구조

```cpp
struct News {};
struct User {};
struct Channel {};

vector<News> news;
vector<Channel> channels;
vector<User> users;

unordered_map<int, int> newsMap;
unordered_map<int, int> channelMap;
unordered_map<int, int> userMap;

int newsCnt;
int channelCnt;
int userCnt;

priority_queue<News> newsPQ;
struct Data {}
```

```cpp
int get_newsIndex(int mNewsID) {}
int get_channelIndex(int mChannelID) {}
int get_userIndex(int mUID) {}
void update_news(int mTime) {}
```

## User Solution API

```cpp
void init(int N, int K) {}
```
- N 명의 유저와 뉴스 알림 서비스를 제공하는 K 개의 뉴스 채널이 있다.
- 현재 시각은 0 이고, 제공된 뉴스는 없다.

```cpp
void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[]) {}
```
- mTime 시각에 mUID 유저는 뉴스 알림을 받기 위해 mNum 개의 뉴스 채널 mChannelIDs[] 에 각각 등록한다.
- mTime 시각에 유저에게 보내지는 뉴스 알림이 있는 경우 먼저 알림을 보낸 후, mUID 유저를 뉴스 채널에 등록한다.

```cpp
int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID) {}
```
- mTime 시각에 mDelay 시간이 있는 mNewsID 뉴스가 mChannelID 뉴스 채널에 제공되고, mChannelID 뉴스 채널에 알림을 등록한 유저의 수를 반환한다.
- mChannelID 뉴스 채널은 (mTime + mDelay) 시각에 뉴스 알림을 등록한 유저들에게 mNewsID 뉴스 알림을 보낸다.

```cpp
void cancelNews(int mTime, int mNewsID) {}
```
- mTime 시각에 mNewsID 뉴스가 취소되어 삭제된다.
- mNewsID 뉴스가 유저들에게 뉴스 알림이 보내 졌으면 유저에게 있는 mNewsID 뉴스 알림도 삭제되어야 한다.


```cpp
int checkUser(int mTime, int mUID, int mRetIDs[]) {}
```
- mTime 시각에 mUID 유저가 받은 뉴스 알림의 개수를 반환하고, mUID 유저가 받은 뉴스의 ID 를 최신 받은 순서대로 최대 3개 mRetIDs[] 에 저장한다. 삭제된 뉴스 알림은 제외한다.
- mTime 시각에 유저에게 보내지는 뉴스 알림이 있는 경우 먼저 알림을 보낸 후, 유저가 받은 뉴스 알림의 개수를 반환한다.
- 함수 호출 후, mUID 유저가 받은 뉴스 알림은 모두 삭제되어 알림의 개수는 0 이 된다.
- mUID 유저가 같은 시간대에 2개 이상의 뉴스 알림을 받은 경우, 뉴스 ID 가 큰 경우 더 최신이다.
- 받은 뉴스 알림이 2개 이하일 경우 받은 뉴스의 ID만 최신 받은 순서대로 저장한다.
- mUID 유저가 받은 뉴스 알림이 없을 경우 0 을 반환한다.
