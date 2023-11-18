#include <cstdio>
#include <cstring>
#include "hash.h"

//#define STRING_DATA

#ifndef STRING_DATA
struct Data {
    int value, idx;
};
// unordered_map<int, vector<Data>> dataList;
IntMap<LinkedList<Data>> dataList;

#else
struct Data {
    char value[11]; int idx;
};
// unordered_map<string, vector<Data>> dataList;
StrMap<LinkedList<Data>> dataList;
#endif


int main()
{

#ifndef STRING_DATA
    dataList.clear();
    dataList[111].push_back({ 100, 10 });
    dataList[111].push_back({ 200, 20 });
    dataList[222].push_back({ 300, 30 });
    dataList[222].push_back({ 400, 40 });

    printf("%d\n", dataList[111].listSize);
    printf("%d\n", dataList[111].listSize);

#else
    dataList.clear();
    dataList["a"].push_back({ "AAA", 10});
    dataList["a"].push_back({ "BBB", 20 });
    dataList["b"].push_back({ "CCC", 30 });
    dataList["b"].push_back({ "DDD", 40 });

    printf("%d\n", dataList["a"].listSize);
    printf("%d\n", dataList["b"].listSize);
#endif

    return 0;
}