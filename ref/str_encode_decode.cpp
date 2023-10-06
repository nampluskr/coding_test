// https://blog.joonas.io/143
#include <cstdio>

#define HASH_LEN 12          // string length for endcoding
using ull = unsigned long long;

ull encode(const char str[]) {
    ull hash = 0;
    int i = 0;
    for (; str[i] != '\0'; i++) { hash = hash * 27 + str[i] - 'a' + 1; }
    for (; i < HASH_LEN; i++) { hash *= 27;  }
    return hash;
}

void decode(char str[], ull hash) {
    int i = HASH_LEN;
    for (; hash % 27 == 0; i--) { hash /= 27; }
    str[i--] = '\0';
    for (; hash > 0; i--) { str[i] = hash % 27 + 'a' - 1; hash /= 27; }
}

int main()
{
    // encoding
    char s1[10] = "abzzz";
    char s2[10] = "zzzab";
    ull hash1 = encode(s1);
    ull hash2 = encode(s2);

    printf("%s = %lld\n", s1, hash1);
    printf("%s = %lld\n", s2, hash2);

    // decoding
    char str1[10];
    char str2[10];
    decode(str1, hash1);
    decode(str2, hash2);

    printf("%lld = %s\n", hash1, str1);
    printf("%lld = %s\n", hash2, str2);

    return 0;
}
