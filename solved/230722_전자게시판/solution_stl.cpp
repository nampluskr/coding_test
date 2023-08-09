#if 1
// STL 496 ms
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#define MAXL			(10)
#define NUM_USERS		(10000)
#define NUM_MESSAGES	(50000)
#define DELETED		    (1)

struct User {
    char name[MAXL + 1];
    int total;
};
unordered_map<string, int> userMap;
vector<User> users;
int userCnt;

struct Message {
    int mID;
    int user;
    int root;
    int point;
    int total;
    int state;

    int parent;
    vector<int> childList;
};
unordered_map<int, int> messageMap;
vector<Message> messages;
int messageCnt;

struct UserData {
    char name[MAXL + 1];
    int total;

    UserData(char _name[], int _total) { strcpy(name, _name); total = _total; }
    bool operator<(const UserData& user) const {
        return (total < user.total) || (total == user.total && strcmp(name, user.name) > 0);
    }
    bool operator==(const UserData& user) const {
        return total == user.total && strcmp(name, user.name) == 0;
    }
};
struct MessageData {
    int mID;
    int total;

    bool operator<(const MessageData& msg) const {
        return (total < msg.total) || (total == msg.total && mID > msg.mID);
    }
    bool operator==(const MessageData& msg) const {
        return total == msg.total && mID == msg.mID;
    }
};

priority_queue<UserData> userPQ;
priority_queue<MessageData> messagePQ;

//////////////////////////////////////////////////////////////////////////////
int get_userIndex(char mUser[]) {
    int uIdx;
    auto ptr = userMap.find(string(mUser));
    if (ptr == userMap.end()) {
        uIdx = userCnt;
        userMap[string(mUser)] = uIdx;
        userCnt += 1;
    }
    else { uIdx = ptr->second; }
    return uIdx;
}
int get_messageIndex(int mID) {
    int mIdx;
    auto ptr = messageMap.find(mID);
    if (ptr == messageMap.end()) {
        mIdx = messageCnt;
        messageMap[mID] = mIdx;
        messageCnt += 1;
    }
    else { mIdx = ptr->second; }
    return mIdx;
}
void erase_messages(int mIdx) {
    int uIdx = messages[mIdx].user;
    int rIdx = messages[mIdx].root;
    int point = messages[mIdx].point;

    messages[mIdx].state = DELETED;
    users[uIdx].total -= point;
    messages[rIdx].total -= point;

    userPQ.push({ users[uIdx].name, users[uIdx].total });
    messagePQ.push({ messages[rIdx].mID, messages[rIdx].total });

    for (int child : messages[mIdx].childList)
        if (messages[child].state != DELETED) {
            erase_messages(child);
        }
}

//////////////////////////////////////////////////////////////////////////////
void init()
{
    userMap.clear();
    users.clear();	users.resize(NUM_USERS);
    userCnt = 0;

    messageMap.clear();
    messages.clear();	messages.resize(NUM_MESSAGES);
    messageCnt = 0;

    while (!userPQ.empty()) { userPQ.pop(); }
    while (!messagePQ.empty()) { messagePQ.pop(); }
}

int writeMessage(char mUser[], int mID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_messageIndex(mID);		// root message

    // update user
    strcpy(users[uIdx].name, mUser);
    users[uIdx].total += mPoint;

    // update message (root)
    messages[mIdx].mID = mID;
    messages[mIdx].user = uIdx;
    messages[mIdx].root = mIdx;
    messages[mIdx].point = mPoint;
    messages[mIdx].total = mPoint;
    messages[mIdx].parent = -1;

    int ret = users[uIdx].total;

    userPQ.push({ users[uIdx].name, users[uIdx].total });
    messagePQ.push({ messages[mIdx].mID, messages[mIdx].total });

    return ret;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_messageIndex(mID);		// child message
    int pIdx = get_messageIndex(mTargetID);	// parent message

    // update user
    strcpy(users[uIdx].name, mUser);
    users[uIdx].total += mPoint;

    // update message (child)
    messages[mIdx].mID = mID;
    messages[mIdx].user = uIdx;
    messages[mIdx].root = messages[pIdx].root;
    messages[mIdx].point = mPoint;
    messages[mIdx].total = mPoint;
    messages[mIdx].parent = pIdx;

    // update message (parent)
    messages[pIdx].childList.push_back(mIdx);

    // update message (root)
    int rIdx = messages[mIdx].root;
    messages[rIdx].total += mPoint;
    int ret = messages[rIdx].total;

    userPQ.push({ users[uIdx].name, users[uIdx].total });
    messagePQ.push({ messages[rIdx].mID, messages[rIdx].total });

    return ret;
}

int erase(int mID)
{
    int ret;
    int mIdx = get_messageIndex(mID);
    erase_messages(mIdx);

    int rIdx = messages[mIdx].root;
    int uIdx = messages[mIdx].user;
    if (mIdx == rIdx) { ret = users[uIdx].total; }  // message
    else { ret = messages[rIdx].total; }            // comment, reply

    return ret;
}

void getBestMessages(int mBestMessageList[])
{
    auto& Q = messagePQ;
    vector<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto msg = Q.top(); Q.pop();
        int mIdx = get_messageIndex(msg.mID);

        if (messages[mIdx].total != msg.total) continue;
        if (messages[mIdx].state == DELETED) continue;
        if (!Q.empty() && msg == Q.top()) continue;     // 중복 제거

        popped.push_back(mIdx);
        mBestMessageList[cnt] = msg.mID;
        cnt += 1;
    }
    for (int _mIdx : popped) {
        Q.push({ messages[_mIdx].mID, messages[_mIdx].total });
    }
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
    auto& Q = userPQ;
    vector<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto user = Q.top(); Q.pop();
        int uIdx = get_userIndex(user.name);

        if (users[uIdx].total != user.total) continue;
        if (!Q.empty() && user == Q.top()) continue;    // 중복 제거

        popped.push_back(uIdx);
        strcpy(mBestUserList[cnt], user.name);
        cnt += 1;
    }
    for (int uIdx : popped) {
        Q.push({ users[uIdx].name, users[uIdx].total });
    }
}
#endif
