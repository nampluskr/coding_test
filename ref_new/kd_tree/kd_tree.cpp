#if 1
// https://www.geeksforgeeks.org/find-and-insertion-in-DIM-dimensional-tree/
// https://rosettacode.org/wiki/K-d_tree#C

#include <cstdio>

const int DIM = 2;

bool cmp(int key1[], int key2[]) {
	for (int i = 0; i < DIM; ++i)
		if (key1[i] != key2[i])
			return false;
	return true;
}

struct KDTree {
	struct TreeNode {
		int key[DIM];
		TreeNode* left;
		TreeNode* right;
	};
	TreeNode* root;

private:
	TreeNode* new_node(int key[]) {
		struct TreeNode* node = new TreeNode;
		for (int i = 0; i < DIM; i++) { node->key[i] = key[i]; }
		node->left = node->right = nullptr;
		return node;
	}
	TreeNode* insert_node(TreeNode* node, int key[], int depth) {
		if (node == nullptr) { return new_node(key); }

		int k = depth % DIM;
		if (key[k] < (node->key[k]))
			node->left = insert_node(node->left, key, depth + 1);
		else
			node->right = insert_node(node->right, key, depth + 1);
		return node;
	}
	TreeNode* find_node(TreeNode* node, int key[], int depth) {
		if (node == nullptr) { return node; }
		if (cmp(node->key, key)) { return node; }

		int k = depth % DIM;
		if (key[k] < node->key[k])
			return find_node(node->left, key, depth + 1);
		else
			return find_node(node->right, key, depth + 1);
	}

public:
	void clear() { root = nullptr; }
	void insert(int key[]) {
		root = insert_node(root, key, 0);
	}
	bool find(int key[]) {
		TreeNode* node = find_node(root, key, 0);
		if (node != nullptr) return true;
		return false;
	}
};
KDTree kdt;


int main()
{
	int points[][DIM] = { {3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19} };
	int n = sizeof(points) / sizeof(points[0]);

	kdt.clear();

	for (int i = 0; i < n; i++)
		kdt.insert(points[i]);

	int key1[] = { 10, 19 };
	printf(">> %d\n", kdt.find(key1));

	int key2[] = { 12, 19 };
	printf(">> %d\n", kdt.find(key2));

	return 0;
}


#endif