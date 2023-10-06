// https://blog.joonas.io/143
#include <cstdio>
#include <unordered_map>
using namespace std;

#define MAX_ENCODING    10      // string length for endcoding
#define MAX_USERS       100
using ull = unsigned long long;

struct User {
    ull intName;        // endcoded ull value
    int age;
};
User users[MAX_USERS];
int userCnt;

template<typename Type>
struct LinkedList {
    struct ListNode {
        Type data;
        ListNode* next;
    };
    ListNode* head;
    ListNode* tail;

    void clera() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        ListNode* node = new ListNode({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

#define MAX_TABLE   50007
template<typename Type1, typename Type2>
struct HashMap {
    struct MapData {
        Type1 key;
        Type2 value;
    };
    LinkedList<MapData> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clera(); }
    int find(const Type1& key) {
        int hashkey = key % MAX_TABLE;
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (node->data.key == key)
                return node->data.value;
        }
        return -1;
    }
    void emplace(const Type1& key, const Type2& value) {
        int hashkey = key % MAX_TABLE;
        table[hashkey].push_back({ key, value });
    }
};
HashMap<ull, int> userMap;


////////////////////////////////////////////////////////////////////
ull encode(const char str[]) {
    ull hash = 0;
    int i = 0;
    for (; str[i] != '\0'; i++) { hash = hash * 27 + str[i] - 'a' + 1; }
    for (; i < MAX_ENCODING; i++) { hash *= 27; }
    return hash;
}

void decode(char str[], ull hash) {
    int i = MAX_ENCODING;
    for (; hash % 27 == 0; i--) { hash /= 27; }
    str[i--] = '\0';
    for (; hash > 0; i--) { str[i] = hash % 27 + 'a' - 1; hash /= 27; }
}

int get_userIndex(ull key) {
    int uIdx;
    auto ret = userMap.find(key);
    if (ret == -1) {
        uIdx = userCnt++;
        userMap.emplace(key, uIdx);
    }
    else { uIdx = ret; }
    return uIdx;
}

////////////////////////////////////////////////////////////////////
void init() {
    for (int i = 0; i < MAX_USERS; i++) { users[i] = {}; }
    userCnt = 0;
    userMap.clear();
}

void add_user(const char name[], int age) {
    ull key = encode(name);
    int uIdx = get_userIndex(key);

    users[uIdx].intName = key;
    users[uIdx].age = age;
}

void query(const char name[]) {
    ull key = encode(name);
    int uIdx = get_userIndex(key);
    char strName[MAX_ENCODING]; decode(strName, users[uIdx].intName);

    printf("%10s[%lld]: %d\n", strName, key, users[uIdx].age);
}

int main()
{
    init();

    add_user("a", 10);
    add_user("aa", 20);
    add_user("b", 30);
    add_user("bb", 40);

    query("bb");
    query("b");
    query("aa");
    query("a");

    return 0;
}
