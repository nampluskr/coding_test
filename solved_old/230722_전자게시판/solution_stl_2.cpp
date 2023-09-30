#if 0
// (���ذ�) STL xxx ms: ������ �߰� ������ ��ť�� ����
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

// �� �׽�Ʈ ���̽����� ������� ���� 10,000 �����̴�.
// �� �׽�Ʈ ���̽����� ��� �Լ��� ȣ�� Ƚ���� 50,000 �����̴�.
// mID : ��, ���, ��� ID (1 �� mID �� 1,000,000,000)
struct User {
    char name[MAXL + 1];
    int sum_points;
    //vector<int> messageList;

    void update();
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
    void update();
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

priority_queue<UserData> userPQ;
priority_queue<MessageData> messagePQ;

void Reply::del() {
    if (state != DELETED) {
        state = DELETED;
        users[uIdx].sum_points -= point;
        if (messages[mIdx].state != DELETED) { messages[mIdx].sum_points -= point; }
    }
}
void Comment::del() {
    if (state != DELETED) {
        state = DELETED;
        users[uIdx].sum_points -= point;
        if (messages[mIdx].state != DELETED) { messages[mIdx].sum_points -= point; }

        for (int rIdx : replyList) { replies[rIdx].del(); }
    }
}
void Message::del() {
    if (state != DELETED) {
        state = DELETED;
        users[uIdx].sum_points -= point;
        //sum_points -= point;

        for (int cIdx : commentList) { comments[cIdx].del(); }
    }
}

void User::update() { userPQ.push({ name, sum_points }); }
void Message::update() { messagePQ.push({ mID, sum_points}); }

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

    while (!userPQ.empty()) { userPQ.pop(); }
    while (!messagePQ.empty()) { messagePQ.pop(); }
}

// �� ���� ��ϵ� �� ����� mUser�� ���� ����Ʈ
int writeMessage(char mUser[], int mID, int mPoint)
{
    int uIdx = get_userIndex(mUser);
    int mIdx = get_messageIndex(mID);
    int ret;

    // Update user
    //strcpy(users[uIdx].name, mUser);
    users[uIdx].sum_points += mPoint;
    //users[uIdx].messageList.push_back(mIdx);

    // Add message
    messages[mIdx].mID = mID;
    messages[mIdx].type = MESSAGE;
    messages[mIdx].point = mPoint;
    messages[mIdx].sum_points += mPoint;
    messages[mIdx].uIdx = uIdx;

    // update userPQ, messagePQ
    users[uIdx].update();
    messages[mIdx].update();

    ret = users[uIdx].sum_points;
    return ret;
}

// ��ϵ� �� �ۼ��� ��� �Ǵ� ����� �޷� �ִ� ���� ���� ����Ʈ
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

        users[uIdx].update();
        messages[comments[mIdx].mIdx].update();

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

        users[uIdx].update();
        messages[replies[mIdx].mIdx].update();

        ret = messages[replies[mIdx].mIdx].sum_points;
    }
    return ret;
}

// mID�� ���� ID�� ��� ������� ���� ����Ʈ, mID�� ��� �Ǵ� ����� ID�� ��� ���� ���� ����Ʈ
int erase(int mID)
{
    int mIdx = get_messageIndex(mID);
    int ret;

    // Erase message
    if (messages[mIdx].type == MESSAGE) {
        messages[mIdx].del();

        users[messages[mIdx].uIdx].update();
        //messages[mIdx].update();

        ret = users[messages[mIdx].uIdx].sum_points;
    }
    // Erase comment
    else if (comments[mIdx].type == COMMENT) {
        comments[mIdx].del();

        users[comments[mIdx].uIdx].update();
        messages[comments[mIdx].mIdx].update();

        ret = messages[comments[mIdx].mIdx].sum_points;
    }
    // Erase reply
    else if (replies[mIdx].type == REPLY) {
        replies[mIdx].del();

        users[replies[mIdx].uIdx].update();
        messages[replies[mIdx].mIdx].update();

        ret = messages[replies[mIdx].mIdx].sum_points;
    }
    return ret;
}

// ���� ����Ʈ�� ���� ���� �۵��� ID�� ����� �迭
// ���� ���� ����Ʈ�� ���� ��� ID�� �� ���� ���� ID�� �� ���� �´�.
void getBestMessages(int mBestMessageList[])
{
    priority_queue<MessageData>& Q = messagePQ;
    vector<int> ret;
    vector<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto message = Q.top(); Q.pop();
        int mIdx = get_messageIndex(message.mID);

        if (messages[mIdx].type != MESSAGE) continue;
        if (messages[mIdx].sum_points != message.sum_points) continue;

        popped.push_back(mIdx);
        if (messages[mIdx].state != DELETED) {
            ret.push_back(message.mID);
            mBestMessageList[cnt] = message.mID;
            cnt += 1;
        }
    }
    for (int mIdx: popped) { Q.push({ messages[mIdx].mID, messages[mIdx].sum_points }); }
}

// ���� ����Ʈ�� ���� ���� ����ڵ��� �̸��� ����� �迭
// ���� ���� ����Ʈ�� ���� ��� �̸��� ���� ������ �� �ռ� ������� �̸��� �� ���� �´�.
void getBestUsers(char mBestUserList[][MAXL + 1])
{
    priority_queue<UserData>& Q = userPQ;
    vector<string> ret;
    vector<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto user = Q.top(); Q.pop();
        int uIdx = get_userIndex(user.name);

        if (users[uIdx].sum_points != user.sum_points) continue;

        popped.push_back(uIdx);
        ret.push_back(string(user.name));
        strcpy(mBestUserList[cnt], user.name);
        cnt += 1;
    }
    for (int uIdx: popped) { Q.push({ users[uIdx].name, users[uIdx].sum_points }); }
}
#endif