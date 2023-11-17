#include <cstdio>

#define MAX_TABLE   (32)        // 2^n = pow(2, n) = (1 << n)
#define ALPHA       2654435769  // 2^32 * (sqrt(5) - 1) / 2
#define MAX_ENCODING    4       // array size = 27 * 27 * 27 * 27

using ull = unsigned long long;
ull encode(const char str[]) {
    ull hashkey = 0;
    int i = 0;
    for (; str[i]; i++) { hashkey = hashkey * 27 + str[i] - 'a' + 1; }
    for (; i < MAX_ENCODING; i++) { hashkey *= 27;  }
    return hashkey;
}

void decode(char str[], int hashkey) {
    int i = MAX_ENCODING;
    for (; hashkey % 27 == 0; i--) { hashkey /= 27;  }
    str[i--] = '\0';
    for (; hashkey > 0; i--) { str[i] = hashkey % 27 + 'a' - 1; hashkey /= 27; }
}

int inthash(ull key) {
    ull hashkey = key * ALPHA;
    return hashkey & (MAX_TABLE - 1);
}

int strhash(const char key[]) {
    unsigned long hashkey = 5381;
    int c;
    while (c = *key++) { hashkey = (((hashkey << 5) + hashkey) + c) % MAX_TABLE; }
    return hashkey % MAX_TABLE;
}

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
        ListNode* node = new ListNode({ data, nullptr});
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

template<typename Type1, typename Type2>
struct HashMap {
    struct MapData {
        Type1 key;
        Type2 value;
    };
    LinkedList<MapData> table[MAX_TABLE];

    void clear() { for (int i = 0; i < MAX_TABLE; i++) table[i].clear(); }
    Type2 find(const Type1& key) {
        int hashkey = inthash(key);
        for (auto node = table[hashkey].head; node; node = node->next) {
            if (node->data.key == key)
                return node->data.value;
        }
        return -1;
    }
    void emplace(const Type1& key, const Type2& value) {
        int hashkey = inthash(key);
        table[hashkey].push_back({ key, value });
    }
};
HashMap<ull, int> userMap;

int userCnt = 0;
int get_userIndex(const char str[]) {
    ull key = encode(str);
    int uIdx;
    auto ret = userMap.find(key);
    if (ret == -1) {
        uIdx = userCnt++;
        userMap.emplace(key, uIdx);
    }
    else { uIdx = ret; }
    return uIdx;
}

int main()
{
    int table[MAX_TABLE];
    int cnt = 0;

    // init
    for (int i = 0; i < MAX_TABLE; i++) {
        table[i] = 0;
    }

    // hash
    for (int i = 0; i < 26; i++) {
        //int hashkey = inthash(1024 + i);
        char str[] = "";
        str[0] = 'a' + i;
        //int hashkey = strhash(str);
        int hashkey = inthash(encode(str));
        table[hashkey] += 1;
        printf("hashkey = %d\n", hashkey);
    }

    // result
    for (int i = 0; i < MAX_TABLE; i++) {
        cnt += table[i];
        printf("table[%d] = %d\n", i, table[i]);
    }
    printf("cnt = %d\n", cnt);

    return 0;
}
