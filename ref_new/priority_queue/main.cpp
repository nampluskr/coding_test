#include <cstdio>
#include <cstring>
#include "pq.h"

//#define STRING_DATA 1

#ifndef STRING_DATA
struct Data {
    int value, idx;
    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

#else
struct Data {
    char value[11];
    int idx;
    bool operator<(const Data& data) const {
        return (strcmp(this->value, data.value) > 0) || 
               (strcmp(this->value, data.value) == 0 && idx > data.idx);
    }
};
#endif

PQ<Data> stl_pq;                    // STL
PriorityQueue<Data> manual_pq;      // Manual

int main()
{
    //auto& Q = stl_pq;
    auto& Q = manual_pq;

#ifndef STRING_DATA
    Q.clear();

    Q.push({ 30, 1 });
    Q.push({ 10, 2 });
    Q.push({ 20, 3 });
    Q.push({ 20, 1 });

    printf("[PQ] size = %d\n", Q.size());
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();
        printf("value = %d, idx = %d\n", data.value, data.idx);
    }
    printf("[PQ] size = %d\n", Q.size());

#else
    Q.clear();

    Q.push({ "ccc", 1});
    Q.push({ "aaa", 2});
    Q.push({ "bbb", 3});
    Q.push({ "bbb", 1});

    printf("[PQ] size = %d\n", Q.size());
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();
        printf("value = %s, idx = %d\n", data.value, data.idx);
    }
    printf("[PQ] size = %d\n", Q.size());

#endif
    return 0;
}