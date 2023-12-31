﻿#if 1
#include <vector>           // 링크드 리스트
#include <unordered_map>    // 해시맵
//#include <queue>          // 우큐
using namespace std;

#define ABS(x)      ((x) < 0 ? -(x) : (x))
#define MAX(a, b)   ((a) < (b) ? (b) : (a))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

#define MAX_TOWERS  50001
#define MAX_COLOERS (5 + 1)
#define MAX_N       5001        
#define MAX_BUCKETS (71 + 1)    // sqrt(5001) + 1

#define ADDED       0
#define REMOVED     1
#define INF         0x7fffffff

int N;                          // 평원 한 변의 길이 ( 10 ≤ N ≤ 5,000 )
int bucket_size;                // sqrt(N) 파티션 크기
int num_buckets;                // ceil((double)N / bucket_size) 파티션 개수

struct Tower {
    int mRow, mCol, mColor, state;

    //int dist(int mRow, int mCol) { return ABS(this->mRow - mRow) + ABS(this->mCol - mCol); }
    int check(int mRow, int mCol, int mDis) {
        int minR = MAX(mRow - mDis, 1), maxR = MIN(mRow + mDis, N);
        int minC = MAX(mCol - mDis, 1), maxC = MIN(mCol + mDis, N);
        return (minR <= this->mRow) && (this->mRow <= maxR) && 
               (minC <= this->mCol) && (this->mCol <= maxC);
    }
};
Tower towers[MAX_TOWERS];
int towerCnt;
unordered_map<int, int> towerMap;

//vector<int> towerList[MAX_COLOERS];
vector<int> buckets[MAX_COLOERS][MAX_BUCKETS][MAX_BUCKETS];

//struct Data { // 우큐
//    int idx, dist;
//    bool operator<(const Data& data) const { return this->dist > data.dist; }
//};

/////////////////////////////////////////////////////////////////////
// k-D Tree Source Code: https://rosettacode.org/wiki/K-d_tree#C

bool compare(const int pt1[], const int pt2[]) {
    return (pt1[0] == pt2[0]) && (pt1[1] == pt2[1]);
}

int distance(const int pt1[], const int pt2[]) {
    return ABS(pt1[0] - pt2[0]) + ABS(pt1[1] - pt2[1]);
}

struct KDTree {
    struct TreeNode {
        int point[2], idx;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    TreeNode* best;
    int best_dist;

private:
    TreeNode* new_node(const TreeNode& data) { 
        TreeNode* node = new TreeNode(data);
        node->left = node->right = nullptr;
        return node;
    }
    TreeNode* insert_node(TreeNode* node, const TreeNode& data, int depth) {
        if (node == nullptr) { return new_node(data); }
        if (data.point[depth % 2] < node->point[depth % 2])
            node->left = insert_node(node->left, data, depth + 1);
        else
            node->right = insert_node(node->right, data, depth + 1);
        return node;
    }
    void nearest_node(TreeNode* node, const int point[], int depth) {
        if (node == nullptr) return;

        if (towers[node->idx].state != REMOVED) {
            int cur_dist = distance(node->point, point);
            if (best == nullptr || cur_dist < best_dist) {
                best_dist = cur_dist;
                best = node;
            }
            if (best_dist == 0) return;     // exact match
        }

        int diff = node->point[depth % 2] - point[depth % 2];
        nearest_node(diff > 0 ? node->left : node->right, point, depth + 1);

        if (ABS(diff) >= best_dist) return;
        nearest_node(diff > 0 ? node->right : node->left, point, depth + 1);
    }

public:
    void clear() { root = nullptr; }
    void insert(const TreeNode& data) { root = insert_node(root, data, 0); }
    int nearest(const int point[]) {
        best = nullptr;
        best_dist = INF;
        nearest_node(root, point, 0);
        if (best != nullptr) return best->idx;
        return -1;
    }
};
KDTree kd_tree[MAX_COLOERS];

/////////////////////////////////////////////////////////////////////
void init(int _N)
{
    N = _N + 1;
    for (int i = 0; i < MAX_TOWERS; i++) { towers[i] = {}; }
    towerCnt = 0;
    towerMap.clear();
    //for (int i = 0; i < MAX_COLOERS; i++) { towerList[i].clear(); }

    bucket_size = sqrt(N);
    num_buckets = ceil((double)N/ bucket_size);

    for (int i = 0; i < MAX_BUCKETS; i++)
        for (int j = 0; j < MAX_BUCKETS; j++) 
            for (int k = 0; k < MAX_COLOERS; k++) { buckets[k][i][j].clear(); }

    for (int i = 0; i < MAX_COLOERS; i++) { kd_tree[i].clear(); }
}

// 50,000
void buildTower(int mRow, int mCol, int mColor)
{
    int key = mRow * 10000 + mCol;
    int tIdx = towerCnt++;
    towerMap.emplace(key, tIdx);
    towers[tIdx] = { mRow, mCol, mColor, ADDED };

    //towerList[mColor].push_back(tIdx);      // 전체 탐색
    //towerList[0].push_back(tIdx);           // 전체 탐색

    int bRow = (mRow - 1) / bucket_size;
    int bCol = (mCol - 1) / bucket_size;
    buckets[mColor][bRow][bCol].push_back(tIdx);    // 파티션
    buckets[0][bRow][bCol].push_back(tIdx);         // 파티션

    kd_tree[mColor].insert({{mRow, mCol}, tIdx});   // k-D Tree
    kd_tree[0].insert({ {mRow, mCol}, tIdx });      // k-D Tree
}

// 1,000
void removeTower(int mRow, int mCol)
{
    int key = mRow * 10000 + mCol;
    auto ptr = towerMap.find(key);
    if (ptr != towerMap.end()) {
        towers[ptr->second].state = REMOVED;
    }
}

// 10,000
int countTower(int mRow, int mCol, int mColor, int mDis)
{
    int ret = 0;
    
    // 전체 탐색 (시간 초과)
    //for (int tIdx: towerList[mColor]) {
    //    if (towers[tIdx].state == REMOVED) continue;
    //    if (towers[tIdx].check(mRow, mCol, mDis)) { ret += 1; }
    //}

    // 부분 탐색 (파티션)
    int spR = MAX((mRow - 1 - mDis) / bucket_size, 0);
    int spC = MAX((mCol - 1 - mDis) / bucket_size, 0);
    int epR = MIN((mRow - 1 + mDis) / bucket_size, num_buckets - 1);
    int epC = MIN((mCol - 1 + mDis) / bucket_size, num_buckets - 1);

    for (int i = spR; i <= epR; i++)
        for (int j = spC; j <= epC; j++)
            for (int tIdx : buckets[mColor][i][j]) {
                if (towers[tIdx].state == REMOVED) continue;
                if (towers[tIdx].check(mRow, mCol, mDis)) { ret += 1; }
            }
    return ret;
}

// 5,000
int getClosest(int mRow, int mCol, int mColor)
{
    int ret = -1;

    // 전체 탐색 (시간 초과)
    //priority_queue<Data> Q;
    //for (int tIdx : towerList[mColor]) {
    //    if (towers[tIdx].state == REMOVED) continue;
    //    Q.push({ tIdx, towers[tIdx].dist(mRow, mCol) });
    //}
    //if (!Q.empty()) { ret = Q.top().dist; }

    // 부분 탐색 (Nearest neighbor search using k-D tree)
    int point[] = { mRow, mCol };
    int tIdx = kd_tree[mColor].nearest(point);
    if (tIdx != -1) { ret = kd_tree[mColor].best_dist; }

    return ret;
}
#endif