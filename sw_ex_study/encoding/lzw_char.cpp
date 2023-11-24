#if 1
// LZW 압축 알고리즘
// https://timewizhan.tistory.com/entry/LZW-Compression
// https://velog.io/@yskyal17/LZW-%EC%95%95%EC%B6%95-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
// https://people.cs.pitt.edu/~kirk/cs1501/assignments/lzw/lzw.cxx
// https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
// 1) LZW는 한 번에 압축한다.
//    (허프만은 트리 생성하는데 한 번; 트리를 바탕으로 압축하는 한 번; 총 2번 문자열을 훑는다.)
// 2) LZW는 허프만 보다 더 단순해서 더 빠르다.
// LZW requires no prior information about the input data stream.
// LZW can compress the input stream in one single pass.
// Another advantage of LZW is its simplicity, allowing fast execution.

#include <cstdio>
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

/*
function LZW_Compress(input):
    initialize the dictionary (create an initial dictionary mapping of ASCII char)
    initialize the output codes
    initialize the current pattern as an empty string
    Create an empty list to store the compressed data

    for char c in the input data:
        add c to the current_pattern
        if current_pattern exists in the dictionary:
            Update the current_pattern as current_pattern + c
        else:
            output the code for the current_pattern
            add the current_pattern + c to the dictionary and generate a new code

    Output the code for the current pattern
    return compressed_data
*/

void encode(const string& input, vector<int>& encoded) {
    unordered_map<string, int> dict;
    for (int i = 0; i < 256; i++) {
        dict[string(1, static_cast<char>(i))] = i;
    }

    string currentPattern = string(1, input[0]);

    for (int i = 1; i < input.size(); i++) {
        string pattern = currentPattern + input[i];
        if (dict.find(pattern) != dict.end()) {
            currentPattern = pattern;
        }
        else {
            encoded.push_back(dict[currentPattern]);
            dict[pattern] = dict.size();
            currentPattern = string(1, input[i]);
        }
    }

    if (!currentPattern.empty()) {
        encoded.push_back(dict[currentPattern]);
    }
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

/*
function LZW_Decompress(compressed):
    initialize the dictionary(create an initial dictionary mapping of ASCII char)
    initialize the previous code
    Create an empty string to store the decompressed data

    for code in compressed_data:
        if code exists in the dictionary:
            output the striing corresponding to the current code
            add the prev_code + the first char of the current_code
        else:
            output the string corresponding to the prev_code + the first char of the prev_code
            add the prev_code + first char of the prev_code to the dict & generate a new code
            update the prev_code as the current_code

     return compressed_data
*/

void decode(const vector<int>& encoded, string& decoded) {
    unordered_map<int, string> dict;
    for (int i = 0; i < 256; i++) {
        dict[i] = string(1, static_cast<char>(i));
    }

    string previousPattern = dict[encoded[0]];
    decoded += previousPattern;

    for (int i = 1; i < encoded.size(); i++) {
        int currentCode = encoded[i];
        string currentPattern;

        if (dict.find(currentCode) != dict.end()) {
            currentPattern = dict[currentCode];
        }
        else {
            currentPattern = previousPattern + previousPattern[0];
        }

        decoded += currentPattern;
        dict[dict.size()] = previousPattern + currentPattern[0];
        previousPattern = currentPattern;
    }
}

// "TOBEORNOTTOBEORTOBEORNOT"
// 84 79 66 69 79 82 78 79 84 256 258 260 265 259 261 263
// "BABAABAAA"
// 66 65 256 257 65 260

string input;
vector<int> encoded;
string decoded;

void print_result() {
    printf("Input: %s\n", input.c_str());
    printf("Encoded: ");
    for (int code : encoded) { printf("%d ", code); }
    printf("\n");
    printf("Decoded: %s\n", decoded.c_str());
}


int main()
{
    input = "BABAABAAA";
    
    encode(input, encoded);
    decode(encoded, decoded);

    print_result();
    return 0;
}
#endif