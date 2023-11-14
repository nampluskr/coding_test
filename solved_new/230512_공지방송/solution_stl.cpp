#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_EMPLOYEES	(8000)
#define ADDED	0
#define REMOVED	1

struct Employee {
	int mStart;
	int mEnd;
	int state;

};
Employee employees[MAX_EMPLOYEES];
int addCnt;
int removeCnt;
unordered_map<int, int> employeeMap;

struct Data {
	int value, idx;
	bool operator<(const Data& data) const { return value > data.value; }
};

////////////////////////////////////////////////////////////////////
int get_employeeIndex(int mId) {
	int eIdx;
	auto ret = employeeMap.find(mId);
	if (ret == employeeMap.end()) {
		eIdx = addCnt++;
		employeeMap.emplace( mId, eIdx );
	}
	else { 
		eIdx = ret->second;
		if (employees[eIdx].state == REMOVED) {
			employees[eIdx].state = ADDED;
			removeCnt -= 1;
		}
	}
	return eIdx;
}

////////////////////////////////////////////////////////////////////
void init()
{
	for (int i = 0; i < MAX_EMPLOYEES; i++) { employees[i] = {}; }
	addCnt = 0;
	removeCnt = 0;
	employeeMap.clear();
}

// 8,000 출퇴근 시각이 등록된 사원 수를 반환한다.
int add(int mId, int mStart, int mEnd)
{
	int eIdx = get_employeeIndex(mId);
	employees[eIdx] = { mStart, mEnd, ADDED };
	int ret = addCnt - removeCnt;
	return ret;
}

// 1,700 출퇴근 시각이 등록된 사원 수를 반환한다.
int remove(int mId)
{
	int eIdx = get_employeeIndex(mId);
	if (employees[eIdx].state == ADDED) {
		employees[eIdx].state = REMOVED;
		removeCnt += 1;
	}
	int ret = addCnt - removeCnt;
	return ret;
}

// 300
int announce(int mDuration, int M)
{
	priority_queue<Data> startQ;
	priority_queue<Data> endQ;

	// Heap sort
	for (int i = 0; i < addCnt; i++) {
		if (employees[i].state == REMOVED) continue;
		startQ.push({ employees[i].mStart, i});
	}

	int ret = -1;
	while (!startQ.empty()) {
		auto data = startQ.top(); startQ.pop();
		int mStart = data.value;
		int endTime = data.value + mDuration - 1;

		// 출근한 임직원들 중에서 방송 끝까지 못듣고 퇴근할 사람을 찾아서 제거한다.
		// ※ [가장 늦은 출근자 출근시각] <= [방송시간] <= [출근시각 + mDuration시각 - 1]
		endQ.push({ employees[data.idx].mEnd, data.idx});
		while (!endQ.empty() && endQ.top().value < endTime) {
			endQ.pop();
		}

		if (endQ.size() >= M) {
			ret = mStart;
			break;
		}
	}
	return ret;
}