#if 1
#include <vector>
#include <unordered_map>
#include <deque>
using namespace std;

#define MAX_N (10000)		// N: 사용자의 수(1 ≤ N ≤ 10, 000)
#define MAX_M (10)			// M : 포털 사이트의 수(2 ≤ M ≤ 10)

struct Data {
	int uIdx;
	int portal;
	int time;
};
struct User {
	deque<Data> visitQ;
	vector<int> visitCnt;
};

vector<User> users;
int userCnt;
unordered_map<int, int> userMap;

int serverCnt;
int serverCapacity;
int serverTime;


///////////////////////////////////////////////////////////////////////////////////////
// N: 사용자의 수(1 ≤ N ≤ 10, 000)
// M : 포털 사이트의 수(2 ≤ M ≤ 10)
// K : 서버의 용량(2 ≤ K ≤ 100, 000)

void init(int N, int M, int K, int uIDList[])
{
	serverCnt = M;
	serverCapacity = K;
	serverTime = 0;

	userCnt = N + 1;
	users.clear();		users.resize(userCnt + 1);
	userMap.clear();

	users[0].visitCnt.resize(M + 1);
	for (int i = 0; i < userCnt; i++) { 
		userMap.emplace(uIDList[i], i + 1);
		users[i + 1].visitCnt.resize(M + 1);
	}
}

void visit(int mUser, int mPortal)
{
	// 저장된 방문 기록이 K 개를 초과하는 경우, 가장 오래전에 저장된 기록이 삭제된다.
	while (!users[0].visitQ.empty() && users[0].visitQ.front().time + serverCapacity <= serverTime) {
		auto oldest = users[0].visitQ.front();
		users[0].visitQ.pop_front();
		users[0].visitCnt[oldest.portal] -= 1;

		users[oldest.uIdx].visitQ.pop_front();
		users[oldest.uIdx].visitCnt[oldest.portal] -= 1;
	}

	int uIdx = userMap[mUser];
	users[uIdx].visitQ.push_back({ uIdx, mPortal, serverTime });
	users[uIdx].visitCnt[mPortal] += 1;
	users[0].visitQ.push_back({ uIdx, mPortal, serverTime });
	users[0].visitCnt[mPortal] += 1;

	serverTime += 1;
}

// users[mUser].visitQ.front()
int getNewestVisited(int mUser, int mList[])
{
	int uIdx = userMap[mUser];
	const auto& Q = users[uIdx].visitQ;

	int ret = Q.size();
	//int cnt = 0;
	//for (auto itr = Q.rbegin(); itr != Q.rend(); itr++) {
	//	mList[cnt++] = itr->portal;
	//}
	//return cnt;
	return ret;
}

// users[mUser].visitQ.back()
int getOldestVisited(int mUser, int mList[])
{
	int uIdx = userMap[mUser];
	const auto& Q = users[uIdx].visitQ;
	//
	//int cnt = 0;
	//for (auto itr = Q.begin(); itr != Q.end(); itr++) {
	//	mList[cnt++] = itr->portal;
	//}
	int ret = Q.size();
	return ret;
}

// users[mUser].visitCnt[portal] --> Heap Sort
void getMostVisited(int mUser, int mList[])
{

}

// users[0].visitCnt[portal] --> Heap Sort
void getMostVisitedAll(int mList[])
{

}
#endif