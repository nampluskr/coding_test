#if 1
// STL 706 ms
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define NUM_NEWS		30000
#define NUM_USERS		500
#define NUM_CHANNELS	500

#define CANCELED	1

struct News {
    int newsID;
    int channelIdx;
    int alarm_time;
    int state;

    bool operator<(const News& data) const { return alarm_time > data.alarm_time; }
};
struct User {
    vector<int> newsList;
};
struct Channel {
    vector<int> userList;
};

vector<News> news;			// ( 1 ¡Â mNewsID ¡Â 1,000,000,000 )
vector<Channel> channels;	// ( 1 ¡Â mChannelID ¡Â 1,000,000,000 )
vector<User> users;			// ( 1 ¡Â mUID ¡Â 1,000,000,000 )

unordered_map<int, int> newsMap;
unordered_map<int, int> channelMap;
unordered_map<int, int> userMap;

int newsCnt;
int channelCnt;
int userCnt;

struct Data {
    int newsID;
    int alarm_time;

    bool operator<(const Data& data) const {
        return (alarm_time < data.alarm_time) ||
            (alarm_time == data.alarm_time && newsID < data.newsID);
    }
};
priority_queue<News> newsPQ;

//////////////////////////////////////////////////////////////////////////////
int get_newsIndex(int mNewsID) {
    int nIdx;
    auto iter = newsMap.find(mNewsID);
    if (iter == newsMap.end()) {
        nIdx = newsCnt;
        newsMap[mNewsID] = nIdx;
        newsCnt += 1;
    }
    else { nIdx = iter->second; }
    return nIdx;
}
int get_channelIndex(int mChannelID) {
    int cIdx;
    auto iter = channelMap.find(mChannelID);
    if (iter == channelMap.end()) {
        cIdx = channelCnt;
        channelMap[mChannelID] = cIdx;
        channelCnt += 1;
    }
    else { cIdx = iter->second; }
    return cIdx;
}
int get_userIndex(int mUID) {
    int uIdx;
    auto iter = userMap.find(mUID);
    if (iter == userMap.end()) {
        uIdx = userCnt;
        userMap[mUID] = uIdx;
        userCnt += 1;
    }
    else { uIdx = iter->second; }
    return uIdx;
}

void update_news(int mTime) {
    auto& Q = newsPQ;
    while (!Q.empty() && Q.top().alarm_time <= mTime) {
        auto data = Q.top(); Q.pop();
        int nIdx = get_newsIndex(data.newsID);

        if (news[nIdx].alarm_time != data.alarm_time) continue;
        if (news[nIdx].state != CANCELED) {
            int cIdx = news[nIdx].channelIdx;
            for (int uIdx : channels[cIdx].userList) {
                users[uIdx].newsList.push_back(nIdx);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int K)
{
    newsMap.clear();
    channelMap.clear();
    userMap.clear();

    news.clear();		news.resize(NUM_NEWS);
    channels.clear();	channels.resize(K);
    users.clear();		users.resize(N);

    newsCnt = 0;
    channelCnt = 0;
    userCnt = 0;

    while (!newsPQ.empty()) { newsPQ.pop(); }
}

// 5,000
void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
    update_news(mTime);

    int uIdx = get_userIndex(mUID);
    for (int i = 0; i < mNum; i++) {
        int cIdx = get_channelIndex(mChannelIDs[i]);
        channels[cIdx].userList.push_back(uIdx);
    }
}

// 30,000
int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
    update_news(mTime);

    int nIdx = get_newsIndex(mNewsID);
    int cIdx = get_channelIndex(mChannelID);

    news[nIdx].newsID = mNewsID;
    news[nIdx].channelIdx = cIdx;
    news[nIdx].alarm_time = mTime + mDelay;

    newsPQ.push(news[nIdx]);

    return channels[cIdx].userList.size();
}

// 3,000
void cancelNews(int mTime, int mNewsID)
{
    update_news(mTime);

    int nIdx = get_newsIndex(mNewsID);
    news[nIdx].state = CANCELED;
}

// 1,000
int checkUser(int mTime, int mUID, int mRetIDs[])
{
    update_news(mTime);

    int ret = 0;
    int uIdx = get_userIndex(mUID);
    priority_queue<Data> Q;

    for (int nIdx : users[uIdx].newsList) {
        if (news[nIdx].state != CANCELED) {
            Q.push({ news[nIdx].newsID, news[nIdx].alarm_time });
        }
    }
    ret = Q.size();

    int cnt = 0;
    while (!Q.empty() && cnt < 3) {
        auto data = Q.top(); Q.pop();
        mRetIDs[cnt] = data.newsID;
        cnt += 1;
    }
    users[uIdx].newsList.clear();
    return ret;
}
#endif