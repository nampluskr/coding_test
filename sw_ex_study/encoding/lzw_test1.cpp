#if 0
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


string input = "BABAABAAA";
vector<int> encoded;
string decoded = "";

void print_result() {
    //printf("Input: %s\n", input);
    //printf("Encoded: %s\n", encoded);
    //printf("Decoded: %s\n", decoded);

    printf("Input: %s\n", input.c_str());
    printf("Encoded: ");
    for (int code : encoded) { printf("%d ", code); }
    printf("\n");
    printf("Decoded: %s\n", decoded.c_str());

}

void concat(string str, char c) {
    int len = 0;
    while (str[len] != '\0') { len++; }
    str[len] = c;
    str[len + 1] = '\0';
}

void encode(const string input, vector<int>& encoded) {
    unordered_map<string, int> dict;
    for (int i = 0; i < 26; i++) {
        char c[2] = "";
        c[0] = 'A' + i;
        dict.emplace(string(c), i);
    }

    string current_pattern = "";
    for (int i = 0; i < input.length(); i++) {
        string new_pattern = current_pattern + input[i];
        if (dict.find(new_pattern) != dict.end()) {
            current_pattern = new_pattern;
        }
        else {
            encoded.push_back(dict[current_pattern]);
            dict.emplace(new_pattern, dict.size());
            current_pattern = string(1, input[i]);
        }
    }
    
    if (!current_pattern.empty()) {
        encoded.push_back(dict[current_pattern]);
    }
    
};

void decode(const string encoded, string& decoded) {

}

int main()
{
    encode(input, encoded);

    print_result();
    return 0;
}
#endif