### Couning Sort

```cpp
// counting sort
// https://plzrun.tistory.com/entry/Counting-Sort-Radix-Sort

#define SIZE	20		// 원소의 최대 개수
#define BASE	6		// 원소의 최대값 (인덱스로 사용)

int A[SIZE] = { 1, 1, 3, 2, 2, 4, 3, 5, 3, 1 };
int N = 10;
int sorted[SIZE];
int count[BASE];

int main()
{
	for (int i = 0; i < BASE; i++) { count[i] = 0; }				// initialize
	for (int i = 0; i < N; i++) { count[A[i]] += 1; }				// count
	for (int i = 1; i < BASE; i++) { count[i] += count[i - 1]; }	// accumulate
	for (int i = N - 1; i >= 0; i--) { sorted[--count[A[i]]] = A[i]; }

	return 0;
}
```

### Radix Sort (10진법)

```cpp
// radix sort
// https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiR68yi-OKCAxWGh1YBHR-SCD4QFnoECAoQAQ&url=https%3A%2F%2Fs.jungol.co.kr%2Fboard%2F77747%2F2sIny0fQchVeGD-1EhLCOo.pdf&usg=AOvVaw19mKpD91xhKbitJEh-KYW5&opi=89978449
// https://plzrun.tistory.com/entry/Counting-Sort-Radix-Sort
// BASE 10 (10진수)

#define SIZE	100		// 원소의 개수

int A[SIZE] = { 3251, 3, 45, 7918, 397, 469, 6138, 42 };
int N = 8;

void radixSort(int A[], int N, int digits=4) {
	int const BASE = 10;
	int B[SIZE], count[BASE];
	int decimal = 1;
	int *a = A, *b = B, *temp;

	for (int i = 0; i < digits; i++, decimal *= BASE) {

		// counting sort for 10^i
		for (int j = 0; j < BASE; j++) { count[j] = 0; }
		for (int j = 0; j < N; j++) { count[a[j] / decimal % BASE] += 1; }
		for (int j = 1; j < BASE; j++) { count[j] += count[j - 1]; }
		for (int j = N - 1; j >= 0; j--) {
			b[--count[a[j] / decimal % BASE]] = a[j];
		}

		temp = a, a = b, b = temp;
		//for (int j = 0; j < N; j++) { A[j] = B[j]; }
	}
}

int main()
{
	radixSort(A, N);

	return 0;
}
```

### Radix Sort (256진법)

```cpp
// radix sort
// https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiR68yi-OKCAxWGh1YBHR-SCD4QFnoECAoQAQ&url=https%3A%2F%2Fs.jungol.co.kr%2Fboard%2F77747%2F2sIny0fQchVeGD-1EhLCOo.pdf&usg=AOvVaw19mKpD91xhKbitJEh-KYW5&opi=89978449
// https://plzrun.tistory.com/entry/Counting-Sort-Radix-Sort
// BASE 256 진수 (= 1 << 8, 2의 배수): 0, 1, 2, ..., 255

#define SIZE 100			// MAX Array Size

int A[SIZE] = { 3251, 3, 45, 7918, 397, 469, 6138, 42 };
int N = 8;

void radixSort(int A[], int N, int digits=16) {
	const int BASE = (1 << 8);
	const int MASK = BASE - 1;
	int B[SIZE], count[BASE];
	int *a = A, *b = B, *temp;

	for (int i = 0; i < digits; i += 8) {

		// counting sort for 256^i
		for (int j = 0; j < BASE; j++) { count[j] = 0; }
		for (int j = 0; j < N; j++) { count[(a[j] >> i) & MASK]++; }
		for (int j = 1; j < BASE; ++j) { count[j] += count[j - 1]; }
		for (int j = N - 1; j >= 0; j--) { b[--count[(a[j] >> i) & MASK]] = a[j]; }

		temp = a, a = b, b = temp;
		//for (int j = 0; j < N; j++) { A[j] = B[j]; }
	}
}

int main()
{
	radixSort(A, N);

	return 0;
}
```

### Huffman Encoding

- [[c++] Huffman Algorithm - 파일 압축 알고리즘](https://hojung-testbench.tistory.com/entry/c-Huffman-Algorithm-%ED%8C%8C%EC%9D%BC-%EC%95%95%EC%B6%95-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    char c;
    int freq;
    Node* left;
    Node* right;

    //bool operator<(const Node* node) const { return this->freq > node->freq; }

};

struct cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};


struct Huffman {
    Node* root = nullptr;
    unordered_map <char, int> ascii;
    unordered_map<char, string> code;
    //priority_queue<Node*> pq;
    priority_queue<Node*, vector<Node*>, cmp> pq;
    string text;

    ~Huffman() {
        releaseTree(root);
        root = nullptr;
        while (!pq.empty()) pq.pop();
    }

    void Start() {
        ifstream file("test.txt");
        while (getline(file, text)) {
            cout << text << "\n";
            for (char a : text) {
                //ascii[a - 'a'] ++;
                //ascii[a].freq++;
                //ascii[a].a = a;
                ++ascii[a];
            }
        }
        //pq에 삽입
        for (const auto iter : ascii) {
            Node* node = new Node;
            node->left = nullptr;
            node->right = nullptr;
            node->c = iter.first;
            node->freq = iter.second;
            pq.push(node);
        }
        makeTree();
        string tmp = "";
        findTree(root, tmp);
    }

    void showCode() {
        for (auto it = code.begin(); it != code.end(); ++it)
        {
            cout << it->first << " : " << it->second << "\n";
        }
    }

    void makeTree() {
        int lim = pq.size() - 1;
        for (int i = 0; i < lim; i++) {
            Node* p = pq.top(); pq.pop();
            Node* q = pq.top(); pq.pop();
            Node* r = new Node;
            r->left = p;
            r->right = q;
            r->freq = p->freq + q->freq;
            r->c = 0;
            pq.push(r);

            cout << "Make Tree시작" << r->left->c << r->left->freq << " " << r->right->c << r->right->freq << "\n";
            cout << "r->a : " << r->c << "r=>freq : " << r->freq << "\n";
        }
        root = pq.top();
        cout << "top is" << root->c << " " << root->freq << "\n";
    }

    void findTree(Node* p, string str) {
        if (p == nullptr) return;
        findTree(p->left, str + '0');
        findTree(p->right, str + '1');
        if (p->c != 0)
        {
            cout << str << "\n";
            //code map에 집어 넣기 
            code[p->c] = str;
        }
    }

    void releaseTree(Node* p)
    {
        if (p == nullptr) return;
        releaseTree(p->left);
        releaseTree(p->right);
        delete p;
        p = nullptr;
    }

};
int main() {

    Huffman T;
    T.Start();
    T.showCode();
    return 0;
}
```
