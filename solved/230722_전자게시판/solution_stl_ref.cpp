#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

#define MAXL (10)
#define MAX_USERS		10'001
#define MAX_MESSAGES	50'001

#define DELETED	1

#define MESSAGE	1
#define COMMENT	2
#define REPLY	3

struct User {
	char name[MAXL];
	int sum_points;

	bool operator<(const User& user) const {
		return (sum_points < user.sum_points) ||
			(sum_points == user.sum_points && strcmp(name, user.name) > 0);
	}
};

unordered_map<string, int> userMap;
vector<User> users;
int userCnt;

unordered_map<int, int> boardMap;
int boardCnt;

struct Data {
	int mID;
	int sum_points;

	bool operator<(const Data& data) const {
		return (sum_points < data.sum_points) ||
			(sum_points == data.sum_points && mID > data.mID);
	}
};

struct Message {
	int mID;
	int type;
	int point;
	int sum_points;
	int uIdx;
	int state;
	vector<int> commentList;

	void add(int uIdx, int mIdx, int mPoint) {
		this->type = MESSAGE;
		this->point = mPoint;
		this->sum_points += mPoint;
		this->uIdx = uIdx;

		users[uIdx].sum_points += mPoint;
	}
	void del();
};
vector<Message> messages;

struct Comment {
	int type;
	int point;
	int uIdx;
	int mIdx;
	int state;
	vector<int> replyList;

	void add(int uIdx, int cIdx, int mIdx, int mPoint) {
		this->type = COMMENT;
		this->point = mPoint;
		this->uIdx = uIdx;
		this->mIdx = mIdx;

		users[uIdx].sum_points += mPoint;
		messages[mIdx].sum_points += mPoint;
		messages[mIdx].commentList.push_back(cIdx);
	}
	void del();
};
vector<Comment> comments;

struct Reply {
	int type;
	int point;
	int uIdx;
	int mIdx;
	int state;

	void add(int uIdx, int rIdx, int cIdx, int mPoint) {
		this->type = REPLY;
		this->point = mPoint;
		this->uIdx = uIdx;
		this->mIdx = comments[cIdx].mIdx;

		users[uIdx].sum_points += mPoint;
		messages[mIdx].sum_points += mPoint;
		comments[cIdx].replyList.push_back(rIdx);
	}
	void del();
};
vector<Reply> replies;

void Message::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		sum_points -= point;

		for (int cIdx : commentList)
			comments[cIdx].del();
	}
}
void Comment::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		messages[mIdx].sum_points -= point;

		for (int rIdx : replyList)
			replies[rIdx].del();
	}
}
void Reply::del() {
	if (state != DELETED) {
		state = DELETED;
		users[uIdx].sum_points -= point;
		messages[mIdx].sum_points -= point;
	}
}

////////////////////////////////////////////////////////////////////
int get_uIdx(char mUser[]) {
	int uIdx;
	auto pos = userMap.find(string(mUser));
	if (pos == userMap.end()) {
		uIdx = userCnt;
		userMap[string(mUser)] = uIdx;
		userCnt += 1;
		strcpy(users[uIdx].name, mUser);
	}
	else {
		uIdx = pos->second;
	}
	return uIdx;
}

int get_mIdx(int mID) {
	int mIdx;
	auto pos = boardMap.find(mID);
	if (pos == boardMap.end()) {
		mIdx = boardCnt;
		boardMap[mID] = mIdx;
		boardCnt += 1;
	}
	else {
		mIdx = pos->second;
	}
	return mIdx;
}

////////////////////////////////////////////////////////////////////
void init()
{
	userMap.clear();
	users.clear();		users.resize(MAX_USERS);
	userCnt = 0;

	boardMap.clear();
	messages.clear();	messages.resize(MAX_MESSAGES);
	comments.clear();	comments.resize(MAX_MESSAGES);
	replies.clear();	replies.resize(MAX_MESSAGES);
	boardCnt = 0;
}

int writeMessage(char mUser[], int mID, int mPoint)
{
	int uIdx = get_uIdx(mUser);
	int mIdx = get_mIdx(mID);
	int ret;

	messages[mIdx].mID = mID;
	messages[mIdx].add(uIdx, mIdx, mPoint);
	ret = users[uIdx].sum_points;
	return ret;
}

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
	int uIdx = get_uIdx(mUser);
	int mIdx = get_mIdx(mID);
	int targetIdx = get_mIdx(mTargetID);
	int ret;

	if (messages[targetIdx].type == MESSAGE) {
		comments[mIdx].add(uIdx, mIdx, targetIdx, mPoint);
		ret = messages[targetIdx].sum_points;
	}
	else if (comments[targetIdx].type == COMMENT) {
		replies[mIdx].add(uIdx, mIdx, targetIdx, mPoint);
		ret = messages[comments[targetIdx].mIdx].sum_points;
	}
	return ret;
}

int erase(int mID)
{
	int mIdx = get_mIdx(mID);
	int ret;

	if (messages[mIdx].type == MESSAGE) {
		messages[mIdx].del();
		ret = users[messages[mIdx].uIdx].sum_points;
	}
	else if (comments[mIdx].type == COMMENT) {
		comments[mIdx].del();
		ret = messages[comments[mIdx].mIdx].sum_points;
	}
	else if (replies[mIdx].type == REPLY) {
		replies[mIdx].del();
		ret = messages[replies[mIdx].mIdx].sum_points;
	}
	return ret;
}

void getBestMessages(int mBestMessageList[])
{
	priority_queue<Data> Q;
	for (int mIdx = 0; mIdx < boardCnt; mIdx++) {
		if (messages[mIdx].type != MESSAGE) continue;
		if (messages[mIdx].state == DELETED) continue;

		Q.push({ messages[mIdx].mID, messages[mIdx].sum_points });
	}

	vector<Data> popped;
	int cnt = 0;
	while (!Q.empty() && cnt < 5) {
		Data data = Q.top(); Q.pop();

		popped.push_back(data);
		mBestMessageList[cnt] = data.mID;
		cnt += 1;
	}
	for (const auto& data : popped) {
		Q.push(data);
	}
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
	priority_queue<User> Q;
	for (int uIdx = 0; uIdx < userCnt; uIdx++) {
		Q.push(users[uIdx]);
	}

	vector<User> popped;
	int cnt = 0;
	while (!Q.empty() && cnt < 5) {
		User user = Q.top(); Q.pop();
		int uIdx = get_uIdx(user.name);

		popped.push_back(users[uIdx]);
		strcpy(mBestUserList[cnt], user.name);
		cnt += 1;
	}
	for (const auto& user : popped) {
		Q.push(user);
	}
}
#endif