#if 1
// STL 633 ms / Manual 618 ms
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

#define MAX_MICROBES    12001   // init() + add()
#define MAX_DAYS        1000001 // (0 <= mDay <= 1,000,000)

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

#define MAX_TABLE   12007
struct HashMap {
    struct StrData {
        char key[12];
        int value;

        //StrData() { strcpy(this->key, ""); this->value = 0; }
        StrData(const char key[], const int value) {
            strcpy(this->key, key); this->value = value;
        }
    };
    LinkedList<StrData> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    int hash(const char key[]) {
        unsigned long hash = 5381;
        int c;
        while (c = *key++) {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        return hash % MAX_TABLE;
    }
    int find(const char key[]) {
        int hashkey = hash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (strcmp(node->data.key, key) == 0)
                return node->data.value;
        }
        return -1;
    }
    void emplace(const char key[], const int value) {
        int hashkey = hash(key);
        table[hashkey].push_back({ key, value });
    }
};

struct Microbe {
    int parent;
    int depth;
};
Microbe microbes[MAX_MICROBES];
HashMap microbeMap;
int microbeCnt;

#define NUM_VALES   1000001 // MAX_DAYS
#define BUCKET_SIZE 1000    // sqrt(num_values)
#define NUM_BUCKETS 1001    // ceil((double)num_values / bucket_size)

struct Partition {
    int buckets[NUM_BUCKETS];   // base (not 구값합)
    int values[NUM_VALES];      // 생존 기간
    int N;                      // bucket size

    void init() {
        N = BUCKET_SIZE;
        for (int i = 0; i < NUM_BUCKETS; i++) { buckets[i] = 0; }
        for (int i = 0; i < NUM_VALES; i++) { values[i] = 0; }
    }
    void update(int left, int right, int value) {
        int s = left / N;
        int e = right / N;

        if (s == e) {
            for (int i = left; i <= right; i++) { values[i] += value; }
            return;
        }
        while (left / N == s) { values[left++] += value; }
        while (right / N == e) { values[right--] += value; }
        for (int i = s + 1; i <= e - 1; i++) { buckets[i] += value; }
    }
    int query(int idx) { return values[idx] + buckets[idx / N]; }
};
Partition part;

/////////////////////////////////////////////////////////////////////
int get_microbeIndex(const char mName[]) {
    int mIdx;
    auto ret = microbeMap.find(mName);
    if (ret == -1) {
        mIdx = microbeCnt++;
        microbeMap.emplace(mName, mIdx);
    }
    else { mIdx = ret; }
    return mIdx;
}

int get_LCA(int x, int y) {
    if (microbes[x].depth < microbes[y].depth) { swap(x, y); }
    while (microbes[x].depth != microbes[y].depth) {
        x = microbes[x].parent;
    }
    while (x != y) {
        x = microbes[x].parent;
        y = microbes[y].parent;
    }
    return x;
}

/////////////////////////////////////////////////////////////////////
void init(char mAncestor[], int mLastday)
{
    for (int i = 0; i < MAX_MICROBES; i++) { microbes[i] = {}; }
    microbeMap.clear();
    microbeCnt = 0;

    int mIdx = get_microbeIndex(mAncestor);
    microbes[mIdx].parent = -1;
    microbes[mIdx].depth = 0;

    part.init();
    part.update(0, mLastday, 1);
}

// 12,000
int add(char mName[], char mParent[], int mFirstday, int mLastday)
{
    int mIdx = get_microbeIndex(mName);
    int pIdx = get_microbeIndex(mParent);
    microbes[mIdx].parent = pIdx;
    microbes[mIdx].depth = microbes[pIdx].depth + 1;

    part.update(mFirstday, mLastday, 1);

    int ret = microbes[mIdx].depth;
    return ret;
}

// 50,000
int distance(char mName1[], char mName2[])
{
    int x = get_microbeIndex(mName1);
    int y = get_microbeIndex(mName2);
    int lca = get_LCA(x, y);

    int ret = microbes[x].depth + microbes[y].depth - 2 * microbes[lca].depth;
    return ret;
}

// 30,000
int count(int mDay)
{
    int ret = part.query(mDay);
    return ret;
}
#endif