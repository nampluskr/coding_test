#if 1
// STL 546 ms
#include <vector>
#include <queue>
using namespace std;

#define NUM_HOTELS	1000
#define NUM_ROOMS	100001

struct CheckInOut {
    int check_in;
    int check_out;
};

struct Room {
    int rID;
    int info[4];
    int price;
    vector<CheckInOut> checkList;

    bool check_date(int check_in, int check_out) {
        for (const auto& date : checkList) {
            if (!(check_out <= date.check_in || check_in >= date.check_out))
                return false;
        }
        return true;
    }
    void update_roomPQ();
};
vector<Room> rooms;
//int roomCnt;

struct Hotel {
    int total_price;
    vector<int> roomList;
};
vector<Hotel> hotels;
//int hotelCnt;

struct Data {
    int rID;
    int price;
    bool operator<(const Data& data) const {
        return (price > data.price) ||
            (price == data.price && rID > data.rID);
    }
};
priority_queue<Data> roomPQ[11][11][5][5];

void Room::update_roomPQ() {
    roomPQ[info[0]][info[1]][info[2]][info[3]].push({ rID, price });
}

//////////////////////////////////////////////////////////////////////////////
void init(int N, int mRoomCnt[])
{
    rooms.clear();	rooms.resize(NUM_ROOMS);
    //roomCnt = 0;

    hotels.clear();	hotels.resize(N + 1);
    //hotelCnt = N;

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            for (int k = 0; k < 5; k++)
                for (int l = 0; l < 5; l++)
                    while (!roomPQ[i][j][k][l].empty()) { roomPQ[i][j][k][l].pop(); }
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

    vector<int> popped;
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
    for (int _rID : popped) { Q.push({ _rID, rooms[_rID].price }); }

    return rID;
}

// 500
int riseCosts(int mHotelID)
{
    for (int rID : hotels[mHotelID].roomList) {
        hotels[mHotelID].total_price -= rooms[rID].price;
        rooms[rID].price *= 1.1;
        hotels[mHotelID].total_price += rooms[rID].price;

        rooms[rID].update_roomPQ();
    }
    return hotels[mHotelID].total_price;
}
#endif