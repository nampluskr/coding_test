### Hash Talbe [int -> int] 작성중

```cpp
#if 1
#include <vector>
using namespace std;

#define MAX_HEAP_SIZE   100
#define MAX_TABLE       77

struct ListNode {
    int Idx;
    ListNode* next;
};

struct UnorderedMap {
    ListNode heap[MAX_HEAP_SIZE];
    int hrp = 0;
    ListNode* table[MAX_TABLE];

    void clear() { hrp = 0; }
    int hash(int carID) {
        int hashkey = carID % MAX_TABLE;
        return hashkey;
    }
    void insert(int carID, int Idx) {
        int hashkey = hash(carID);
        ListNode* node = &heap[hrp];
        node->Idx = Idx;
        node->next = table[hashkey];
        table[hashkey] = node;
        hrp += 1;
    }
    int find(int carID) {
        int hashkey = hash(carID);
        ListNode* temp = carMap.table[hashkey];
        while (temp != 0) {
            int Idx = temp->Idx;
            if (cars[Idx].carID == carID)
                return Idx;
            temp = temp->next;
        }
        return -1;
    }

};
UnorderedMap carMap;

struct Car {
    int carID;
};
vector<Car> cars;
int carCnt;

// carMap & cars 필요
int get_carIndex(int carID) {
    int cIdx;
    auto ret = carMap.find(carID);
    if (ret != -1) {
        cIdx = carCnt;
        carMap.insert(carID, cIdx);
        carCnt += 1;
    }
    else { cIdx = ret; }
    return cIdx;
}

int main()
{

    return 0;
}

#endif
```
