#if 0
// Manual 536 ms: Array + Linked List
// Priority Queue: roomPQ[11][11][5][5] 메모리 초과
//#include <vector>
#include <queue>
using namespace std;

#define NUM_HOTELS	1000
#define NUM_ROOMS	100001

template<typename Type>
struct LinkedList {
    struct List {
        Type data;
        List* next;
    };
    List* head;
    List* tail;

    void push_back(const Type& data) {
        List* node = new List({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct CheckInOut {
    int check_in;
    int check_out;
};

struct Room {
    int rID;
    int info[4];
    int price;
    LinkedList<CheckInOut> checkList;

    bool check_date(int check_in, int check_out) {
        for (auto ptr = checkList.head; ptr; ptr = ptr->next) {
            auto date = ptr->data;
            if (!(check_out <= date.check_in || check_in >= date.check_out))
                return false;
        }
        return true;
    }
    void update_roomPQ();
};
Room rooms[NUM_ROOMS];
//int roomCnt;

struct Hotel {
    int total_price;
    LinkedList<int> roomList;
};
Hotel hotels[NUM_HOTELS];
//int hotelCnt;

struct Data {
    int rID;
    int price;
    bool operator<(const Data& data) const {
        return (price > data.price) ||
            (price == data.price && rID > data.rID);
    }
};

#if 1
template<typename Type>
struct PriorityQueue {
    priority_queue<Type> heap;

    void init() { while (!heap.empty()) heap.pop(); }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue {
    Type heap[NUM_ROOMS];
    int heapSize = 0;

    void init() { heapSize = 0; }
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
};
#endif

PriorityQueue<Data> roomPQ[11][11][5][5];

void Room::update_roomPQ() {
    roomPQ[info[0]][info[1]][info[2]][info[3]].push({ rID, price });
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mRoomCnt[])
{
    for (int i = 0; i < NUM_ROOMS; i++) { rooms[i] = {}; }
    for (int i = 0; i < NUM_HOTELS + 1; i++) { hotels[i] = {}; }

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            for (int k = 0; k < 5; k++)
                for (int l = 0; l < 5; l++)
                    roomPQ[i][j][k][l].init();
}

void addRoom(int mHotelID, int mRoomID, int mRoomInfo[])
{
    rooms[mRoomID].rID = mRoomID;
    rooms[mRoomID].info[0] = mRoomInfo[0];
    rooms[mRoomID].info[1] = mRoomInfo[1];
    rooms[mRoomID].info[2] = mRoomInfo[2];
    rooms[mRoomID].info[3] = mRoomInfo[3];
    rooms[mRoomID].price = mRoomInfo[4];

    hotels[mHotelID].total_price += rooms[mRoomID].price;
    hotels[mHotelID].roomList.push_back(mRoomID);

    rooms[mRoomID].update_roomPQ();
}

// 10,000
int findRoom(int mFilter[])
{
    int rID = -1;
    int check_in = mFilter[0];
    int check_out = mFilter[1];
    auto& Q = roomPQ[mFilter[2]][mFilter[3]][mFilter[4]][mFilter[5]];

    LinkedList<int> popped;
    while (!Q.empty()) {
        auto data = Q.top(); Q.pop();

        if (data.price != rooms[data.rID].price) continue;

        popped.push_back(data.rID);
        if (rooms[data.rID].check_date(check_in, check_out)) {
            rID = data.rID;
            rooms[rID].checkList.push_back({ check_in, check_out });
            break;
        }
    }
    for (auto ptr = popped.head; ptr; ptr = ptr->next) {
        auto _rID = ptr->data;
        Q.push({ _rID, rooms[_rID].price });
    }

    return rID;
}

// 500
int riseCosts(int mHotelID)
{
    for (auto ptr = hotels[mHotelID].roomList.head; ptr; ptr = ptr->next) {
        auto rID = ptr->data;
        hotels[mHotelID].total_price -= rooms[rID].price;
        rooms[rID].price *= 1.1;
        hotels[mHotelID].total_price += rooms[rID].price;

        rooms[rID].update_roomPQ();
    }
    return hotels[mHotelID].total_price;
}
#endif