#if 0
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
#endif