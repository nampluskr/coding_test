#if 0
// STL 19608 ms: 함수 호출시 마다 힙정렬
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAXL            (10)
#define NUM_USERS       (10001)
#define NUM_MESSAGES    (50001)

#define MESSAGE     1
#define COMMENT     2
#define REPLY       3

#define DELETED     1

// 각 테스트 케이스에서 사용자의 수는 10,000 이하이다.
// 각 테스트 케이스에서 모든 함수의 호출 횟수는 50,000 이하이다.
// mID : 글, 댓글, 답글 ID (1 ≤ mID ≤ 1,000,000,000)
struct User {
    char name[MAXL + 1];
    int sum_points;
    vector<int> messageList;
};
struct Message {
    int mID;
    int type;
    int point;
    int sum_points;
    int uIdx;
    vector<int> commentList;
    int state;

    void del();
};
struct Comment {
    int type;
    int point;
    int uIdx;
    int mIdx;
    vector<int> replyList;
    int state;

    void del();
};
struct Reply {
    int type;
    int point;
    int uIdx;
    int mIdx;
    int state;

    void del();
};

unordered_map<string, int> userMap;
vector<User> users;
int userCnt;

unordered_map<int, int> messageMap;
vector<Message> messages;
vector<Comment> comments;
vector<Reply> replies;
int messageCnt;

void Reply::del() {
    if (state != DELETED) {
        state = DELETED;
        messages[mIdx].sum_points -= point;
        users[uIdx].sum_points -= point;
    }
}
void Comment::del() {
    if (state != DELETED) {
        state = DELETED;
        messages[mIdx].sum_points -= point;
        users[uIdx].sum_points -= point;

        for (int rIdx : replyList) { replies[rIdx].del(); }
    }
}
void Message::del() {
    if (state != DELETED) {
        state = DELETED;
        sum_points -= point;
        users[uIdx].sum_points -= point;

        for (int cIdx : commentList) { comments[cIdx].del(); }
    }
}

struct UserData {
    char name[MAXL + 1];
    int sum_points;

    UserData(char _name[], int _sum_points) {
        strcpy(name, _name);
        sum_points = _sum_points;
    }
    bool operator<(const UserData& user) const {
        return (sum_points < user.sum_points) ||
            (sum_points == user.sum_points && strcmp(name, user.name) > 0);
    }
};
struct MessageData {
    int mID;
    int sum_points;
    bool operator<(const MessageData& message) const {
        return (sum_points < message.sum_points) ||
            (sum_points == message.sum_points && mID > message.mID);
    }
};

///////////////////////////////////////////////////////////////////////////////////
int get_userIndex(char mUser[]) {
    int uIdx;
    auto pos = userMap.find(string(mUser));
    if (pos == userMap.end()) {
        uIdx = userCnt;
        userMap[string(mUser)] = uIdx;
        userCnt += 1;
        strcpy(users[uIdx].name, mUser);
    }
    else { uIdx = pos->second; }
    return uIdx;
}

int get_messageIndex(int mID) {
    int mIdx;
    auto pos = messageMap.find(mID);
    if (pos == messageMap.end()) {
        mIdx = messageCnt;
        messageMap[mID] = mIdx;
        messageCnt += 1;
    }
    else { mIdx = pos->second; }
    return mIdx;
}
///////////////////////////////////////////////////////////////////////////////////
void init()
{
    userMap.clear();
    users.clear();      users.resize(NUM_USERS);
    userCnt = 0;

    messageMap.clear();
    messages.clear();   messages.resize(NUM_MESSAGES);
    comments.clear();   comments.resize(NUM_MESSAGES);
    replies.clear();    replies.resize(NUM_MESSAGES);
    messageCnt = 0;
}

// 새 글이 등록된 후 사용자 mUser의 총합 포인트
int writeMessage(char mUser[], int mID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_messageIndex(mID);
    int ret;

    // Update user
    //strcpy(users[uIdx].name, mUser);
    users[uIdx].sum_points += mPoint;
    users[uIdx].messageList.push_back(mIdx);

    // Add message
    messages[mIdx].mID = mID;
    messages[mIdx].type = MESSAGE;
    messages[mIdx].point = mPoint;
    messages[mIdx].sum_points += mPoint;
    messages[mIdx].uIdx = uIdx;

    ret = users[uIdx].sum_points;
    return ret;
}

// 등록된 후 작성된 댓글 또는 답글이 달려 있는 글의 총합 포인트
int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_messageIndex(mID);
    int targetIdx = get_messageIndex(mTargetID);
    int ret;

    // Add comment to message
    if (messages[targetIdx].type == MESSAGE) {
        comments[mIdx].type = COMMENT;
        comments[mIdx].point = mPoint;
        comments[mIdx].uIdx = uIdx;
        comments[mIdx].mIdx = targetIdx;

        messages[targetIdx].sum_points += mPoint;
        messages[targetIdx].commentList.push_back(mIdx);
        users[uIdx].sum_points += mPoint;

        ret = messages[comments[mIdx].mIdx].sum_points;
    }
    // Add reply to comment
    else if (comments[targetIdx].type == COMMENT) {
        replies[mIdx].type = REPLY;
        replies[mIdx].point = mPoint;
        replies[mIdx].uIdx = uIdx;
        replies[mIdx].mIdx = comments[targetIdx].mIdx;

        comments[targetIdx].replyList.push_back(mIdx);
        messages[replies[mIdx].mIdx].sum_points += mPoint;
        users[uIdx].sum_points += mPoint;

        ret = messages[replies[mIdx].mIdx].sum_points;
    }
    return ret;
}

// mID가 글의 ID인 경우 사용자의 총합 포인트, mID가 댓글 또는 답글의 ID인 경우 글의 총합 포인트
int erase(int mID)
{
    int mIdx = get_messageIndex(mID);
    int ret;

    // Erase message
    if (messages[mIdx].type == MESSAGE) {
        messages[mIdx].del();
        ret = users[messages[mIdx].uIdx].sum_points;
    }
    // Erase comment
    else if (comments[mIdx].type == COMMENT) {
        comments[mIdx].del();
        ret = messages[comments[mIdx].mIdx].sum_points;
    }
    // Erase reply
    else if (replies[mIdx].type == REPLY) {
        replies[mIdx].del();
        ret = messages[replies[mIdx].mIdx].sum_points;
    }
    return ret;
}

// 총합 포인트가 가장 높은 글들의 ID가 저장될 배열
// 만약 총합 포인트가 같은 경우 ID가 더 작은 글의 ID가 더 먼저 온다.
void getBestMessages(int mBestMessageList[])
{
    priority_queue<MessageData> Q;
    for (int uIdx = 0; uIdx < userCnt; uIdx++)
        for (int mIdx : users[uIdx].messageList)
            if (messages[mIdx].state != DELETED) {
                Q.push({ messages[mIdx].mID, messages[mIdx].sum_points });
            }
    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto message = Q.top(); Q.pop();
        int mIdx = get_messageIndex(message.mID);

        if (messages[mIdx].sum_points != message.sum_points) continue;

        mBestMessageList[cnt] = message.mID;
        cnt += 1;
    }
}

// 총합 포인트가 가장 높은 사용자들의 이름이 저장될 배열
// 만약 총합 포인트가 같은 경우 이름이 사전 순으로 더 앞선 사용자의 이름이 더 먼저 온다.
void getBestUsers(char mBestUserList[][MAXL + 1])
{
    priority_queue<UserData> Q;
    for (int uIdx = 0; uIdx < userCnt; uIdx++) {
        Q.push({ users[uIdx].name, users[uIdx].sum_points });
    }
    int cnt = 0;
    while (!Q.empty() && cnt < 5) {
        auto user = Q.top(); Q.pop();
        int uIdx = get_userIndex(user.name);

        if (users[uIdx].sum_points != user.sum_points) continue;

        strcpy(mBestUserList[cnt], user.name);
        cnt += 1;
    }
}
#endif