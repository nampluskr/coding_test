# 230722_전자게시판

## 자료구조 / 변수 / 함수

```cpp
struct User {};
struct Message {};
struct Comment {};
struct Reply {};

vector<User> users;         int userCnt;
vector<Message> messages;   int messageCnt;
vector<Comment> comments;
vector<Reply> replies;

unordered_map<string, int> userMap;
unordered_map<int, int> boardMap;

struct UserData {};
struct MessageData {};

priority_queue<UserData> userPQ;
priority_queue<MessageData> messagePQ;
```

```cpp
int get_userIndex(char mUser[]) {}
int get_messageIndex(int mID) {}
void erase_messages(int mIdx) {}
```

## User code API

```cpp
void init() {}
```

```cpp
int writeMessage(char mUser[], int mID, int mPoint) { return 0; }
```
- 이름이 mUser인 사용자가 ID가 mID이고 포인트가 mPoint인 글을 작성하고 게시판에 등록한다. 글이 등록된 후 사용자의 총합 포인트를 반환한다.
- 사용자의 총합 포인트는 사용자가 작성한 글, 댓글, 답글의 포인트를 모두 합한 값이다. 이때 삭제된 글, 댓글, 답글의 포인트는 포함되지 않는다.

```cpp
int commentTo(char mUser[], int mID, int mTargetID, int mPoint) { return 0; }
```
- 이름이 mUser인 사용자가 ID가 mTargetID인 글 또는 댓글에 ID가 mID이고 포인트가 mPoint인 댓글 또는 답글을 단다.
- mTargetID가 글의 ID이면 글 mTargetID에 댓글 mID를 달고 글 mTargetID의 총합 포인트를 반환한다.
- mTargetID가 댓글의 ID이면 댓글 mTargetID에 답글 mID를 달고 댓글 mTargetID가 달린 글의 총합 포인트를 반환한다.
- 글의 총합 포인트는 글의 포인트와 그 글에 달린 댓글들과 답글들의 포인트를 모두 합한 값이다. 이때 삭제된 댓글들과 답글들의 포인트는 합하지 않는다.

```cpp
int erase(int mID) { return 0; }
```
- ID가 mID인 글 또는 댓글 또는 답글을 삭제한다.
- mID가 글의 ID인 경우 삭제된 글 mID를 작성한 사용자의 총합 포인트를 반환한다.
- mID가 댓글 또는 답글의 ID인 경우 삭제된 댓글 또는 답글이 달려 있었던 글의 총합 포인트를 반환한다.

```cpp
void getBestMessages(int mBestMessageList[]) {}
```
- 총합 포인트가 가장 높은 글 5개의 ID를 내림차순으로 mBestMessageList에 저장한다.
- 만약 총합 포인트가 같은 경우 ID가 더 작은 글의 ID가 더 먼저 온다.
- 총합 포인트가 i번째로 가장 높은 글의 ID를 mBestMessageList[i – 1]에 저장한다. (1 ≤ i ≤ 5)

```cpp
void getBestUsers(char mBestUserList[][MAXL + 1]) {}
```
- 총합 포인트가 가장 높은 사용자 5명의 이름을 내림차순으로 mBestUserList에 저장한다.
- 만약 총합 포인트가 같은 경우 이름이 사전 순으로 더 앞선 사용자의 이름이 더 먼저 온다.
- 총합 포인트가 i번째로 가장 높은 사용자의 이름을 mBestUserList[i – 1]에 저장한다. (1 ≤ i ≤ 5)

## 제약사항

1. 각 테스트 케이스 시작 시 init() 함수가 한 번 호출된다.
2. 각 테스트 케이스에서 사용자의 수는 10,000 이하이다.
3. 각 테스트 케이스에서 모든 함수의 호출 횟수는 50,000 이하이다.
