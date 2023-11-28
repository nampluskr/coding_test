### Huffman endcoding

```cpp
// https://hojung-testbench.tistory.com/entry/c-Huffman-Algorithm-%ED%8C%8C%EC%9D%BC-%EC%95%95%EC%B6%95-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
// https://www.geeksforgeeks.org/huffman-decoding/
// https://github.com/jdanene/huffman-encoding/blob/master/src/huff.cpp

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;


struct Node {
	char c;
	int freq;
	Node* left;
	Node* right;

	Node(char c, int freq) { 
		this->c = c; this->freq = freq; left = nullptr; right = nullptr;
	}
};

struct Compare{
	bool operator()(const Node* a, const Node* b) { return a->freq > b->freq; }
};

struct Huffman {
	unordered_map<char, int> hit;
	unordered_map<char, string> code;
	priority_queue<Node*, vector<Node*>, Compare> Q;

	void store(Node* node, string str) {
		if (node == nullptr) return;
		if (node->c != 0) { code[node->c] = str; }
		store(node->left, str + '0');
		store(node->right, str + '1');
	}

	void encode(const string text, string& encoded) {
		// count freq of characters
		for (char c : text) { hit[c]++; }

		// PQ push (char, freq)
		for (auto iter : hit) {
			Node* node = new Node(iter.first, iter.second);
			Q.push(node);
		}

		// Huffman tree
		while (Q.size() > 1) {
			Node* left = Q.top(); Q.pop();
			Node* right = Q.top(); Q.pop();
			Node* top = new Node(0, left->freq + right->freq);
			top->left = left;
			top->right = right;
			Q.push(top);
		}

		store(Q.top(), "");
		for (char c : text) { encoded += code[c]; }
	}

	void decode(const string encoded, string& decoded) {
		Node* node = Q.top();
		for (char c : encoded) {
			node = (c == '0') ? node->left : node->right;

			// reached leaf node
			if (node->left == nullptr && node->right == nullptr) {
				decoded += node->c;
				node = Q.top();
			}
		}
	}

	void printCodes() {
		for (auto iter : code) {
			printf("%c [%2d] >> %s\n", iter.first, hit[iter.first], iter.second.c_str());
		}
	}
};


int main()
{
	//string text = "aaaabbbccd!!!!!@@@@";
	string text = "MELLOW YELLOW FELLOW";
	string encoded = "";
	string decoded = "";

	Huffman H;
	H.encode(text, encoded);
	H.decode(encoded, decoded);
	H.printCodes();

	printf("text:    %s\n", text.c_str());
	printf("encoded: %s\n", encoded.c_str());
	printf("decoded: %s\n", decoded.c_str());

	return 0;
}
```

### LZW encoding

```cpp
// https://junstar92.tistory.com/191 (see corner case!)
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;


void encode(const string& text, vector<int>& encoded) {
    unordered_map<string, int> dict;
    //for (int i = 0; i < 256; i++) { dict[string(1, static_cast<char>(i))] = i; }
    for (int i = 0; i < 26; i++) { dict[string(1, 'a' + i)] = i; }
    for (int i = 0; i < 26; i++) { dict[string(1, 'A' + i)] = 26 + i; }
    for (int i = 0; i < 9; i++) { dict[string(1, '0' + i)] = 26 + 26 + i; }
    dict[string(1, ' ')] = 26 + 26 + 9;

    string ptn = "";

    for (char c: text) {
        string cur_ptn = ptn + c;
        if (dict.find(cur_ptn) != dict.end()) {
            ptn = cur_ptn;
        }
        else {
            encoded.push_back(dict[ptn]);
            dict[cur_ptn] = dict.size();
            ptn = string(1, c);
        }
    }

    if (!ptn.empty()) {
        encoded.push_back(dict[ptn]);
    }
}


void decode(const vector<int>& encoded, string& decoded) {
    unordered_map<int, string> dict;
    //for (int i = 0; i < 256; i++) { dict[i] = string(1, static_cast<char>(i)); }
    for (int i = 0; i < 26; i++) { dict[i] = string(1, 'a' + i); }
    for (int i = 0; i < 26; i++) { dict[26 + i] = string(1, 'A' + i); }
    for (int i = 0; i < 9; i++) { dict[26 + 26 + i] = string(1, '0' + i); }
    dict[26 + 26 + 9] = string(1, ' ');

    string ptn = dict[encoded[0]];
    decoded += ptn;

    for (int i = 1; i < encoded.size(); i++) {
        int cur_code = encoded[i];
        string cur_ptn;

        if (dict.find(cur_code) != dict.end()) {
            cur_ptn = dict[cur_code];
        }
        else {
            cur_ptn = ptn + ptn[0];
        }

        decoded += cur_ptn;
        dict[dict.size()] = ptn + cur_ptn[0];
        ptn = cur_ptn;
    }
}

void print(const vector<int>& vec) {
    for (int k : vec) { printf("%d ", k); }
    printf("\n");
}

int main()
{
    string text = "MELLOW YELLOW FELLOW";
    vector<int> encoded;
    string decoded = "";

    encode(text, encoded);
    decode(encoded, decoded);

    printf("text:    %s\n", text.c_str());
    printf("encoded: "); print(encoded);
    printf("decoded: %s\n", decoded.c_str());

    return 0;
}
```
