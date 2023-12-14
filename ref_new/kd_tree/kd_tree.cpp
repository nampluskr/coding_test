#if 1
// https://www.geeksforgeeks.org/find-and-insertion-in-DIM-dimensional-tree/
// https://rosettacode.org/wiki/K-d_tree#C

#include <cstdio>
#include <cmath>

#define ABS(x)  ((x > 0)? (x): -(x))
#define DIM     2

bool compare(const int pt1[], const int pt2[]) {
    for (int i = 0; i < DIM; ++i)
        if (pt1[i] != pt2[i])
            return false;
    return true;
}

int distance(const int pt1[], const int pt2[]) {
    int ret = 0;
    for (int i = 0; i < DIM; i++)
        ret += ABS(pt1[i] - pt2[i]);
    return ret;
}

struct TreeNode {
    int point[DIM];
    int value;
    TreeNode* left;
    TreeNode* right;
};

struct KDTree {
    TreeNode* root;

private:
    TreeNode* new_node(const TreeNode& data) {
        TreeNode* node = new TreeNode;
        for (int i = 0; i < DIM; i++) { node->point[i] = data.point[i]; }
        node->value = data.value;
        node->left = node->right = nullptr;
        return node;
    }
    TreeNode* insert_node(TreeNode* node, const TreeNode& data, int depth) {
        if (node == nullptr) { return new_node(data); }
        if (data.point[depth % DIM] < node->point[depth % DIM])
            node->left = insert_node(node->left, data, depth + 1);
        else
            node->right = insert_node(node->right, data, depth + 1);
        return node;
    }
    TreeNode* find_node(TreeNode* node, const int point[], int depth) {
        if (node == nullptr) { return node; }
        if (compare(node->point, point) == true) { return node; }
        if (point[depth % DIM] < node->point[depth % DIM])
            return find_node(node->left, point, depth + 1);
        else
            return find_node(node->right, point, depth + 1);
    }
    TreeNode* best = nullptr;
    int min_dist = 0x7fffffff;

    void nearest_node(TreeNode* node, const int point[], int depth) {
        if (node == nullptr) return;

        int cur_dist = distance(node->point, point);
        if (best == nullptr || cur_dist < min_dist) {
            min_dist = cur_dist;
            best = node;
        }
        if (min_dist == 0) return;     // exact match

        int diff = node->point[depth % DIM] - point[depth % DIM];
        nearest_node(diff > 0 ? node->left : node->right, point, depth + 1);

        if (ABS(diff) >= min_dist) return;
        nearest_node(diff > 0 ? node->right : node->left, point, depth + 1);
    }

public:
    void clear() { root = nullptr; }
    void insert(const TreeNode& data) {
        root = insert_node(root, data, 0);
    }
    int find(const int point[]) {
        TreeNode* node = find_node(root, point, 0);
        if (node != nullptr) return node->value;
        return -1;
    }
    int nearest(const int point[]) {
        nearest_node(root, point, 0);
        if (best != nullptr) return best->value;
        return -1;
    }
};
KDTree kdt;


int main()
{
    TreeNode points[] = { {{3, 6}, 0}, {{17, 15}, 1}, {{13, 15}, 2}, {{6, 12}, 3}, {{9, 1}, 4}, {{2, 7}, 5}, {{10, 19}, 6} };
    int n = sizeof(points) / sizeof(points[0]);

    kdt.clear();
    for (int i = 0; i < n; i++)
        kdt.insert(points[i]);

    int pt1[] = { 10, 19 };
    printf(">> %d\n", kdt.find(pt1));

    int pt2[] = { 12, 19 };
    printf(">> %d\n", kdt.find(pt2));

    int pt[] = { 10, 10 };
    printf(">> %d\n", kdt.nearest(pt));

    return 0;
}


#endif