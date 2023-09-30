#if 0
// Manual 973 ms / STL 706 ms

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int listSize = 0;

    void clear() { head = nullptr; tail = nullptr; listSize = 0; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
        listSize += 1;
    }
    int size() { return listSize; }
};

#define MAX_TABLE   30007
struct HashMap {
    struct Node {
        int key;
        int value;
    };
    LinkedList<Node> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int find(int key) {
        int hashkey = key % MAX_TABLE;
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (node->data.key == key)
                return node->data.value;
        }
        return -1;
    }
    void emplace(int key, int value) {
        int hashkey = key % MAX_TABLE;
        table[hashkey].push_back({ key, value });
    }
};

#define MAX_HEAP 30000
template<typename Type>
struct PriorityQueue {
    Type heap[MAX_HEAP];
    int heapSize = 0;

    void push(const Type& data) { 
        heap[heapSize] = data;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current]) {
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

        while (current * 2 + 1 < heapSize) {
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
    int size() { return heapSize; }
};

//////////////////////////////////////////////////////////////////////////////

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
    LinkedList<int> newsList;
};
struct Channel {
    LinkedList<int> userList;
};

News news[NUM_NEWS];			// ( 1 ¡Â mNewsID ¡Â 1,000,000,000 )
Channel channels[NUM_CHANNELS];	// ( 1 ¡Â mChannelID ¡Â 1,000,000,000 )
User users[NUM_USERS];			// ( 1 ¡Â mUID ¡Â 1,000,000,000 )

HashMap newsMap;
HashMap channelMap;
HashMap userMap;

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
PriorityQueue<News> newsPQ;

//////////////////////////////////////////////////////////////////////////////
int get_newsIndex(int mNewsID) {
    int nIdx;
    auto iter = newsMap.find(mNewsID);
    if (iter == -1) {
        nIdx = newsCnt;
        newsMap.emplace(mNewsID, nIdx);
        newsCnt += 1;
    }
    else { nIdx = iter; }
    return nIdx;
}
int get_channelIndex(int mChannelID) {
    int cIdx;
    auto iter = channelMap.find(mChannelID);
    if (iter == -1) {
        cIdx = channelCnt;
        channelMap.emplace(mChannelID, cIdx);
        channelCnt += 1;
    }
    else { cIdx = iter; }
    return cIdx;
}
int get_userIndex(int mUID) {
    int uIdx;
    auto iter = userMap.find(mUID);
    if (iter == -1) {
        uIdx = userCnt;
        userMap.emplace(mUID, uIdx);
        userCnt += 1;
    }
    else { uIdx = iter; }
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
            for (auto node = channels[cIdx].userList.head; node; node = node->next) {
                int uIdx = node->data;
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

    for (int i = 0; i < NUM_NEWS; i++) { news[i] = {}; }
    for (int i = 0; i < K; i++) { channels[i] = {}; }
    for (int i = 0; i < N; i++) { users[i] = {}; }

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
    PriorityQueue<Data> Q;

    for (auto node = users[uIdx].newsList.head; node; node = node->next) {
        int nIdx = node->data;
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