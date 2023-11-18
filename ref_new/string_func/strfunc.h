#pragma once

using ull = unsigned long long;

char* sub_str(const char str[], int start, int len) {
    char* dest = new char[len + 1];
    for (int i = 0; i < len; i++) { dest[i] = str[start + i]; }
    dest[len] = '\0';
    return dest;
}

int str_len(const char str[]) {
    int len = 0;
    while (str[len] != '\0') { len++; }
    return len;
}

int int_len(int x, int radix = 10) {
    int len = 0;
    if (x == 0) { return 1; };
    while (x > 0) { x /= radix; len++; }
    return len;
}

int atoi(const char str[]) {
    int x = 0;
    for (int i = 0; str[i] != '\0'; i++) { x = x * 10 + str[i] - '0'; }
    return x;
}

char* itoa(int x) {
    int len = int_len(x);
    char* str = new char[len + 1];
    for (int i = 0; i < len; i++) { str[len - i - 1] = x % 10 + '0'; x /= 10; }
    str[len] = '\0';
    return str;
}

ull encode(const char str[], int len = 0) {
    ull x = 0;
    int i = 0;
    for (; str[i] != '\0'; i++) { x = x * 27 + str[i] - 'a' + 1; }
    for (; i < len; i++) { x *= 27; }
    return x;
}

char* decode(ull x, int len = 0) {
    if (len == 0) { len = int_len(x, 27); }
    char* str = new char[len + 1];
    int i = len;
    for (; x % 27 == 0; i--) { x /= 27; }
    str[i--] = '\0';
    for (; x > 0; i--) { str[i] = x % 27 + 'a' - 1; x /= 27; }
    return str;
}

void strcpy(char dest[], const char src[]) {
    int i = 0;
    for (; src[i] != '\0'; i++) { dest[i] = src[i]; }
    dest[i] = src[i];
}

int strcmp(const char a[], const char b[]) {
    int i = 0;
    for (; a[i] != '\0'; i++) {
        if (a[i] != b[i]) { return a[i] - b[i]; }
    }
    return a[i] - b[i];
}

void strcat(char a[], const char b[]) {
    int len = str_len(a);
    for (int j = 0; b[j] != '\0'; j++) { a[len++] = b[j]; }
    a[len] = '\0';
}

char* copy(const char str[]) {
    int len = str_len(str);
    char* dest = new char[len + 1];
    for (int i = 0; i < len; i++) { dest[i] = str[i]; }
    dest[len] = '\0';
    return dest;
}

char* str_cat(const char s1[], const char s2[]) {
    int len1 = str_len(s1);
    int len2 = str_len(s2);
    char* dest = new char[len1 + len2 + 1];
    for (int i = 0; i < len1; i++) { dest[i] = s1[i];}
    for (int i = 0; i < len2; i++) { dest[len1 + i] = s2[i]; }
    dest[len1 + len2] = '\0';
    return dest;
}