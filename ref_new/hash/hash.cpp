#include "hash.h"

int intHash(unsigned long long key) {
    return key % MAX_TABLE;
}

#define KNUTH_MAX_TABLE     (1024 * 4)  // 2^n
int knuthHash(unsigned long long key) {
    unsigned long long hash = key * 2654435769;  // 2^32 * (sqrt(5) - 1) / 2
    return hash & (KNUTH_MAX_TABLE - 1);
}

int strHash(const char key[]) {
    unsigned long long hash = 5381;     // Magic number
    int c;
    while (c = *key++) { hash = (((hash << 5) + hash) + c) % MAX_TABLE; }
    return hash % MAX_TABLE;
}