#include "depq.h"

struct Data {
    char value[11];
    int idx;
    bool operator<(const Data& data) const {
        return strcmp(this->value, data.value) > 0;
    }
};

DoubleEndedPQ<Data> Q;

int main () 
{
    Q.clear();

    Q.push({ "ddd", 1 });
    Q.push({ "aaa", 2 });
    Q.push({ "bbb", 3 });
    Q.push({ "ccc", 4 });
    Q.push({ "eee", 5 });
    printf("[DEPQ] size = %d\n", Q.size());

    //while (!Q.empty()) {
    //    auto data = Q.top(); Q.pop_top();
    //    printf("(%s, %d), size = %d\n", data.value, data.idx, Q.size());
    //}

    //while (!Q.empty()) {
    //    auto data = Q.bottom(); Q.pop_bottom();
    //    printf("(%s, %d), size = %d\n", data.value, data.idx, Q.size());
    //}

    while (!Q.empty()) {
        auto top = Q.top(); Q.pop_top();
        printf("Top:    (%s, %d), size = %d\n", top.value, top.idx, Q.size());

        if (!Q.empty()) {
            auto bot = Q.bottom(); Q.pop_bottom();
            printf("Bottom: (%s, %d), size = %d\n", bot.value, bot.idx, Q.size());
        }
    }

    return 0;
}