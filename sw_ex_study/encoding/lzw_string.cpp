#if 0
// LZW 압축 알고리즘
// https://timewizhan.tistory.com/entry/LZW-Compression
// https://people.cs.pitt.edu/~kirk/cs1501/assignments/lzw/lzw.cxx

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

/* LZW Encoding
1     Initialize table with single character strings
2     P = first input character
3     WHILE not end of input stream
4          C = next input character
5          IF P + C is in the string table
6            P = P + C
7          ELSE
8            output the code for P
9          add P + C to the string table
10           P = C
11    END WHILE
12    output code for P
*/

vector<int> encode(const string& input) {
    unordered_map<string, int> dict;
    for (int i = 0; i < 256; ++i) {
        dict[string(1, static_cast<char>(i))] = i;
    }

    string currentPattern;
    vector<int> compressedData;

    for (char c : input) {
        string pattern = currentPattern + c;
        if (dict.find(pattern) != dict.end()) {
            currentPattern = pattern;
        }
        else {
            compressedData.push_back(dict[currentPattern]);
            dict[pattern] = dict.size();
            currentPattern = string(1, c);
        }
    }

    if (!currentPattern.empty()) {
        compressedData.push_back(dict[currentPattern]);
    }

    return compressedData;
}

/* LZW Decoding
1    Initialize table with single character strings
2    OLD = first input code
3    output translation of OLD
4    WHILE not end of input stream
5        NEW = next input code
6        IF NEW is not in the string table
7               S = translation of OLD
8               S = S + C
9        ELSE
10              S = translation of NEW
11       output S
12       C = first character of S
13       OLD + C to the string table
14       OLD = NEW
15   END WHILE
*/

string decode(const vector<int>& compressed) {
    unordered_map<int, string> dict;
    for (int i = 0; i < 256; ++i) {
        dict[i] = string(1, static_cast<char>(i));
    }

    string decompressedData;
    string previousPattern = dict[compressed[0]];
    decompressedData += previousPattern;

    for (size_t i = 1; i < compressed.size(); ++i) {
        int currentCode = compressed[i];
        string currentPattern;

        if (dict.count(currentCode)) {
            currentPattern = dict[currentCode];
        }
        else {
            currentPattern = previousPattern + previousPattern[0];
        }

        decompressedData += currentPattern;
        dict[dict.size()] = previousPattern + currentPattern[0];
        previousPattern = currentPattern;
    }

    return decompressedData;
}

int main() {
    string input = "TOBEORNOTTOBEORTOBEORNOT";
    vector<int> compressed = encode(input);
    string decompressed = decode(compressed);

    cout << "Input: " << input << endl;
    cout << "Compressed: ";
    for (int code : compressed) {
        cout << code << " ";
    }
    cout << endl;
    cout << "Decompressed: " << decompressed << endl;

    return 0;
}
#endif