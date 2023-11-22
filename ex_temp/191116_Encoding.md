### [mainc.cpp]

```cpp
#include <stdio.h>
#include <memory.h>
#include <time.h>

extern int encode(char*, char*, int);
extern void decode(char*, char*, int);

static unsigned long long seed = 5; // seed can be changed

static unsigned int random(void)
{
    return ((unsigned int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

static int  hit[26] = { 82, 15, 28, 43, 127, 22, 20, 61, 30, 2, 8, 40, 24, 67, 75, 19, 1, 60, 63, 91, 28, 10, 24, 2, 20, 1 };
static char dummy1[9999];
static char alpha[963];
static char dummy2[9998];
static char dic[1024][8];
static char dummy3[9997];
static int  dics[1024];
static int  papern;
static char src[65536];
static char dest[65536];
static char dummy4[2182];
static char paper[65536];
static char dummy5[291];
static char bak_paper[65536];

static void build_dic(void)
{
    int i = 0;
    int j = 0;

    for (int c = 0; c < 963; c++)
    {
        if (j >= hit[i])
        {
            i++;
            j = 0;
        }
        alpha[c] = 'a' + i;
        j++;
    }

    for (int c = 0; c < 1024; c++)
    {
        int l = 1 + random() % 7;
        dics[c] = l;
        for (int d = 0; d < l; d++)
            dic[c][d] = alpha[random() % 963];
    }
}

int main(void)
{
    int papern;

    build_dic();

    time_t TIME = clock();
    int    RATE = 0;

    for (int c = 0; c < 100; c++)
    {
        int pl = 0;

        while (true)
        {
            int i = random() % 1024;
            if (pl + dics[i] > 65535) break;

            for (int c = 0; c < dics[i]; c++)
                paper[pl++] = dic[i][c];

            paper[pl++] = ' ';
        }
        papern = pl;

        for (int i = 0; i < papern; i++)
        {
            bak_paper[i] = paper[i];
        }
        int s = encode(src, bak_paper, papern);

        for (int i = s; i < 65536; i++)
        {
            src[i] = 0;
        }

        decode(dest, src, s);

        if (memcmp(paper, dest, papern) != 0)
        {
            RATE += 10000000;
        }
        else
        {
            RATE += s;
        }
    }

    TIME = clock() - TIME;
    printf("SCORE: %.5f\n", RATE + TIME / 100000.);

}
```

### 111

```cpp
#if 1
//SCORE: 2127378
int my_strcmp(char* str1, char* str2, int size) {
    for (int k = 0; k < size; k++) {
        if (str1[k] != str2[k])
            return str1[k] - str2[k];
    }
    return 0;
}

void put_bit(bool* bitNote, int num, int bitNum, int bIdx) {
    if (bitNum > 5) {
        int chk2 = 0;
    }

    for (int k = bIdx; k < bIdx + bitNum; k++) {
        bitNote[k] = num & (1 << (bitNum - (k - bIdx) - 1));
    }
}

int read_bit(bool* bitNote, int start, int len) {
    int result = 0;
    for (int bnum = len - 1; bnum >= 0; bnum--) {
        result += bitNote[start + (len - bnum) - 1] << bnum;
    }
    return result;
}

int encode(char* src, char* paper, int papern) {
    int hitNum = 0;

    int numcnt = 0;

    int sIdx = 0;
    int pIdx = 0;
    //int spaceCnt = 0;
    char my_dic[1024][8];
    int my_dics[1024];
    int vocaCnt = 0;
    bool vocaFlag;

    int first_one;

    bool bitNote[65536 * 8];
    int bIdx = 0;

    char nowstr[8];
    int strlen = 0;
    while (pIdx < papern) {
        if (paper[pIdx] == ' ') {
            //strlen==1 이면 사전등록 안함 -> 손해
            if (strlen == 1) {
                if (nowstr[0] == 'e') {
                    put_bit(bitNote, 8, 4, bIdx); //스페이스바
                    bIdx += 4;
                }
                else if (nowstr[0] == 't') {
                    put_bit(bitNote, 9, 4, bIdx); //스페이스바
                    bIdx += 4;
                }
                else if (nowstr[0] == 'a') {
                    put_bit(bitNote, 10, 4, bIdx); //스페이스바
                    bIdx += 4;
                }
                else {
                    //hitNum++;
                    put_bit(bitNote, strlen, 4, bIdx); //스페이스바
                    bIdx += 4;
                    put_bit(bitNote, nowstr[0] - 'a', 5, bIdx);
                    bIdx += 5;
                }

            }
            else {
                //find in dic
                vocaFlag = false;
                for (int k = 0; k < vocaCnt; k++) {
                    if (my_dics[k] == strlen && my_strcmp(my_dic[k], nowstr, strlen) == 0) {
                        vocaFlag = true;
                        first_one = -1;
                        //0~7:8   8~15:9    16~31:10
                        for (int h = 9; h >= 5; h--) {
                            if ((k & (1 << h)) != 0) {
                                first_one = h + 1;
                                break;
                            }
                        }
                        if (first_one == -1) {
                            //hitNum++;
                            first_one = 6;
                        }
                        put_bit(bitNote, first_one + 5, 4, bIdx); //스페이스바
                        bIdx += 4;
                        put_bit(bitNote, k, first_one, bIdx); //숫자
                        bIdx += first_one;
                        break;
                    }
                }

                //없으면 사전등록 + 적재
                if (vocaFlag == false) {
                    put_bit(bitNote, strlen, 4, bIdx); //스페이스바
                    bIdx += 4;
                    my_dics[vocaCnt] = strlen;
                    for (int k = 0; k < strlen; k++) {
                        my_dic[vocaCnt][k] = nowstr[k];
                        put_bit(bitNote, nowstr[k] - 'a', 5, bIdx);
                        bIdx += 5;
                    }
                    vocaCnt++;
                }
            }
            strlen = 0;
        }
        else {
            nowstr[strlen++] = paper[pIdx];
        }
        pIdx++;
    }

    put_bit(bitNote, 0, 4, bIdx);
    bIdx += 4;

    for (int k = 0; k < papern; k++) {
        src[k] = 0;
    }

    int bitNum;
    for (int k = 0; k < bIdx; k++) {
        sIdx = k / 8;
        bitNum = 7 - (k % 8);
        src[sIdx] += bitNote[k] << bitNum;
    }
    return bIdx / 8 + 1;

}
void decode(char* dest, char* src, int s) {
    for (int a = s; a < 65536; a++) {
        dest[a] = 0;
    }

    char my_dic[1024][8];
    int my_dics[1024];
    int vocaCnt = 0;
    int vocaIdx = 0;

    bool bitNote[65536 * 8];
    int bIdx = 0;
    int pIdx = 0;
    //int sIdx = 0;

    for (int k = 0; k < s; k++) {
        for (int h = 7; h >= 0; h--) {
            bitNote[bIdx++] = src[k] & (1 << h);
        }
    }
    int bSize = bIdx;
    bIdx = 0;

    int bitNum;
    int spaceNum = read_bit(bitNote, 0, 4);
    bIdx += 4;
    bool nextIsNum = false;

    while (bIdx < bSize) {
        if (nextIsNum) {
            bitNum = spaceNum - 5;
            vocaIdx = read_bit(bitNote, bIdx, bitNum);
            bIdx += bitNum;
            for (int k = 0; k < my_dics[vocaIdx]; k++) {
                dest[pIdx++] = my_dic[vocaIdx][k];
            }
        }
        else {
            if (spaceNum == 1) {
                dest[pIdx++] = read_bit(bitNote, bIdx, 5) + 'a';
                bIdx += 5;
            }
            else if (spaceNum == 8) {
                dest[pIdx++] = 'e';
            }
            else if (spaceNum == 9) {
                dest[pIdx++] = 't';
            }
            else if (spaceNum == 10) {
                dest[pIdx++] = 'a';
            }
            else {
                my_dics[vocaCnt] = spaceNum;
                for (int k = 0; k < spaceNum; k++) {
                    dest[pIdx++] = my_dic[vocaCnt][k] = read_bit(bitNote, bIdx, 5) + 'a';
                    bIdx += 5;
                }
                vocaCnt++;
            }
        }

        dest[pIdx++] = ' ';
        spaceNum = read_bit(bitNote, bIdx, 4);
        bIdx += 4;
        if (spaceNum == 0)
            break;
        else if (spaceNum <= 10)
            nextIsNum = false;
        else
            nextIsNum = true;
    }

    return;
}
#endif
```

### []

```cpp
//개선작업: 스페이스바와 사전인덱스 표시 bit수 조절
//SCORE: 1933614
int my_strcmp(char* str1, char* str2, int size) {
    for (int k = 0; k < size; k++) {
        if (str1[k] != str2[k])
            return str1[k] - str2[k];
    }
    return 0;
}

void put_bit(bool* bitNote, int num, int bitNum, int* bIdx) {
    if (bitNum > 5) {
        int chk2 = 0;
    }

    for (int k = *bIdx; k < *bIdx + bitNum; k++) {
        bitNote[k] = num & (1 << (bitNum - (k - *bIdx) - 1));
    }
    *bIdx += bitNum;
}

int read_bit(bool* bitNote, int* bIdx, int len) {
    int result = 0;
    for (int bnum = len - 1; bnum >= 0; bnum--) {
        result += bitNote[*bIdx + (len - bnum) - 1] << bnum;
    }
    *bIdx += len;
    return result;
}

int encode(char* src, char* paper, int papern) {
    int sIdx = 0;
    int pIdx = 0;
    //int spaceCnt = 0;
    char my_dic[1024][8];
    int my_dics[1024];
    int vocaCnt = 0;
    bool vocaFlag;

    int first_one;

    bool bitNote[65536 * 8];
    int bIdx = 0;

    char nowstr[8];
    int strlen = 0;
    while (pIdx < papern) {
        if (paper[pIdx] == ' ') {
            //strlen==1 이면 사전등록 안함 -> 손해
            if (strlen == 1) {
                //hitNum++;
                put_bit(bitNote, strlen, 4, &bIdx); //스페이스바
                put_bit(bitNote, nowstr[0] - 'a', 5, &bIdx);

            }
            else {
                //find in dic
                vocaFlag = false;
                for (int k = 0; k < vocaCnt; k++) {
                    if (my_dics[k] == strlen && my_strcmp(my_dic[k], nowstr, strlen) == 0) {
                        vocaFlag = true;
                        first_one = -1;
                        put_bit(bitNote, 1, 1, &bIdx); //스페이스바
                        put_bit(bitNote, k, 10, &bIdx); //숫자
                        break;
                    }
                }

                //없으면 사전등록 + 적재
                if (vocaFlag == false) {
                    put_bit(bitNote, strlen, 4, &bIdx); //스페이스바
                    my_dics[vocaCnt] = strlen;
                    for (int k = 0; k < strlen; k++) {
                        my_dic[vocaCnt][k] = nowstr[k];
                        put_bit(bitNote, nowstr[k] - 'a', 5, &bIdx);
                    }
                    vocaCnt++;
                }
            }
            strlen = 0;
        }
        else {
            nowstr[strlen++] = paper[pIdx];
        }
        pIdx++;
    }

    put_bit(bitNote, 1, 1, &bIdx);
    put_bit(bitNote, 1023, 10, &bIdx);

    for (int k = 0; k < papern; k++) {
        src[k] = 0;
    }

    int bitNum;
    for (int k = 0; k < bIdx; k++) {
        sIdx = k / 8;
        bitNum = 7 - (k % 8);
        src[sIdx] += bitNote[k] << bitNum;
    }
    return sIdx + 1;

}
void decode(char* dest, char* src, int s) {
    for (int a = s; a < 65536; a++) {
        dest[a] = 0;
    }

    char my_dic[1024][8];
    int my_dics[1024];
    int vocaCnt = 0;
    int vocaIdx = 0;

    bool bitNote[65536 * 8];
    int bIdx = 0;
    int pIdx = 0;

    for (int k = 0; k < s; k++) {
        for (int h = 7; h >= 0; h--) {
            bitNote[bIdx++] = src[k] & (1 << h);
        }
    }
    int bSize = bIdx;
    bIdx = 0;

    int bitNum;
    int spaceNum;
    bool nextIsNum = read_bit(bitNote, &bIdx, 1);;

    while (bIdx < bSize) {
        if (nextIsNum) {
            vocaIdx = read_bit(bitNote, &bIdx, 10);
            if (vocaIdx == 1023)
                break;
            for (int k = 0; k < my_dics[vocaIdx]; k++) {
                dest[pIdx++] = my_dic[vocaIdx][k];
            }
        }
        else {
            spaceNum = read_bit(bitNote, &bIdx, 3);
            if (spaceNum == 1) {
                dest[pIdx++] = read_bit(bitNote, &bIdx, 5) + 'a';
            }
            else {
                my_dics[vocaCnt] = spaceNum;
                for (int k = 0; k < spaceNum; k++) {
                    dest[pIdx++] = my_dic[vocaCnt][k] = read_bit(bitNote, &bIdx, 5) + 'a';
                }
                vocaCnt++;
            }
        }
        dest[pIdx++] = ' ';
        nextIsNum = read_bit(bitNote, &bIdx, 1);
    }
    return;
}
```
