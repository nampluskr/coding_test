#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

#define MAX_N 20

int map[MAX_N][MAX_N];  // 1 �� mMap[][] �� 5
int N;                  // map size


////////////////////////////////////////////////////////////////////
void init(int _N, int mMap[MAX_N][MAX_N])
{
    N = _N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            map[i][j] = mMap[i][j];

}

// M : �������� ũ�� (2 �� M �� 5)
// mStructure: �������� �� �κ��� ���� (1 �� mStructure[] �� 5)
int numberOfCandidate(int M, int mStructure[])
{

    return 0;
}

int maxBlockedRobots(int M, int mStructure[], int mDir)
{

    return 0;
}