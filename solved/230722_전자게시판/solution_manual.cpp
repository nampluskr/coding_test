#if 1
// Manual 713 ms (WS): Array + LinkedList + PriorityQueue
#define _CRT_SECURE_NO_WARNINGS

//#include <vector>
//#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#define MAXL			(10)
#define NUM_USERS		(10000)
#define NUM_MESSAGES	(50000)
#define DELETED		1
#define HEAP_SIZE       (50000)

template<typename Type>
struct LinkedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(const Type& data) {
        Node* node = new Node({data, nullptr});
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct User {
    char name[MAXL + 1];
    int total = 0;
};
unordered_map<string, int> userMap;
User users[NUM_USERS];
int userCnt;

struct Message {
    int mID;
    int user;
    int root;
    int point;
    int total;
    int state;

    int parent;
    LinkedList<int> childList;
};
unordered_map<int, int> messageMap;
Message messages[NUM_MESSAGES];
int messageCnt;

struct UserData {
    char name[MAXL + 1];
    int total;

    UserData() { strcpy(name, ""); total = 0; }
    UserData(char _name[], int _total) { strcpy(name, _name); total = _total; }
    bool operator<(const UserData& user) const {
        return (total < user.total) || (total == user.total && strcmp(name, user.name) > 0);
    }
};
struct MessageData {
    int mID;
    int total;

    bool operator<(const MessageData& msg) const {
        return (total < msg.total) || (total == msg.total && mID > msg.mID);
    }
};

#if 0
template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;
    int heapSize = 0;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue {
    Type heap[HEAP_SIZE];
    int heapSize = 0;

    void init() { heapSize = 0; }
    void push(const Type& data) {
        heap[heapSize] = data;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            Type temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int current = 0;

        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current]) {
                break;
            }
            Type temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
};
#endif

PriorityQueue<UserData> userPQ;
PriorityQueue<MessageData> messagePQ;

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
    //if (messages[rIdx].state != DELETED) {
    //    messagePQ.push({ messages[rIdx].mID, messages[rIdx].total });
    //}

    for (auto ptr = messages[mIdx].childList.head; ptr; ptr=ptr->next) {
        int child = ptr->data;
        if (messages[child].state != DELETED) {
            erase_messages(child);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
void init()
{
    userMap.clear();
    for (int i = 0; i < NUM_USERS; i++) { users[i] = {}; }
    userCnt = 0;

    messageMap.clear();
    for (int i = 0; i < NUM_MESSAGES; i++) { messages[i] = {}; }
    messageCnt = 0;

    //while (!userPQ.empty()) { userPQ.pop(); }
    //while (!messagePQ.empty()) { messagePQ.pop(); }
    userPQ.init();      // set heapSize = 0
    messagePQ.init();   // set heapSize = 0
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
    if (mIdx == rIdx) { ret = users[uIdx].total; }
    else { ret = messages[rIdx].total; }

    return ret;
}

void getBestMessages(int mBestMessageList[])
{
    auto& Q = messagePQ;
    LinkedList<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto msg = Q.top(); Q.pop();
        int mIdx = get_messageIndex(msg.mID);

        if (messages[mIdx].total != msg.total) continue;
        if (messages[mIdx].state == DELETED) continue;

        // 중복 제거
        if (!Q.empty() && msg.mID == Q.top().mID && msg.total == Q.top().total) continue;

        popped.push_back(mIdx);
        mBestMessageList[cnt] = msg.mID;
        cnt += 1;
    }
    for (auto ptr = popped.head; ptr; ptr=ptr->next) {
        int mIdx = ptr->data;
        Q.push({ messages[mIdx].mID, messages[mIdx].total });
    }
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
    auto& Q = userPQ;
    LinkedList<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 5) {
        auto user = Q.top(); Q.pop();
        int uIdx = get_userIndex(user.name);

        if (users[uIdx].total != user.total) continue;

        //중복 제거
        if (!Q.empty() && strcmp(user.name, Q.top().name) == 0 && user.total == Q.top().total) continue;

        popped.push_back(uIdx);
        strcpy(mBestUserList[cnt], user.name);
        cnt += 1;
    }
    for (auto ptr = popped.head; ptr; ptr = ptr->next) {
        int uIdx = ptr->data;
        Q.push({ users[uIdx].name, users[uIdx].total });
    }
}
#endif
