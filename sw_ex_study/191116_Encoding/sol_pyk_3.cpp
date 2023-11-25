// SCORE : 2089212.03194 �ڿ��� 2023.11.10

//myDic��  ���� �� a~z, '\0' ���� 5bit�� ǥ���� �����Ͽ�
//myDic[1024][8] �� myDic[1024][5] �����Ͽ����ϴ�.
//1) encode()
//
//�� str ������ MAX 1024���� paper�� �о� myDic[880][5] �ۼ�
//(seed�� �ٲٸ� Ȯ���غ��� MAX 870ea ������ Ȯ�εǾ� 880���� ����)
//�� myDict�� index�� 0~1023 �����̴� src�� 10bit ������ index�� ����
//
//2) decode()
//�� src���� 10bit ������ �о� myDicIdx ������
//�� myDic[myDicIdx] str�� 8byte�� ��ȯ�Ͽ� dest�� �ű�

#if 0
#define MAX_DIC 880
#define SIZE 20000
#define ARR_SIZE 28

struct Data {
    int dwp;
    int srcSize;

    int strcomp(unsigned char* str1, unsigned char* str2)
    {
        int idx = 0;
        while (1) {
            if (idx == 5)
                return 1;
            else if (str1[idx] != str2[idx])
                return 0;
            idx++;
        }
    }

    void transTo8ByteStr(int idx, char* str, char* arr)
    {
        int tempStrIdx[8] = { 0, };
        int tempIdx = 0;
        int offset = 0;

        for (int i = 0; i < 8; i++) {
            for (int j = 4; j >= 0; j--) {
                int bit = (this->myDic[idx][tempIdx] >> (7 - offset++)) & 1;

                if (offset == 8) {
                    tempIdx++;
                    offset = 0;
                }
                tempStrIdx[i] |= bit << j;
            }
            if (tempStrIdx[i] == 26)
                break;
        }

        for (int i = 0; i < 8; i++) {
            str[i] = arr[tempStrIdx[i]];
            if (arr[tempStrIdx[i]] == '\0')
                break;
        }
    }

    int getIdx(unsigned char* tempStr, unsigned char* arr)
    {
        for (int i = 0; i < dwp; i++) {
            if (strcomp(myDic[i], tempStr) == 1)
                return i;
        }
        return -1;
    }

    int getIdx(unsigned char tok, unsigned char* arr)
    {
        for (int i = 0; i < ARR_SIZE; i++) {
            if (tok == arr[i])
                return i;
        }
        return -1;
    }

    void transTo5ByteStr(unsigned char* tempStr, unsigned char* str, unsigned char* arr) {
        int strIdx = 0;
        int offset = 0;

        for (int i = 0; i < 8; i++) {
            unsigned char tok = str[i];
            int arrIdx = getIdx(tok, arr);

            for (int shift = 4; shift >= 0; shift--) {
                int bit = (arrIdx >> shift) & 1;
                tempStr[strIdx] |= bit << (7 - offset);
                offset++;

                if (offset == 8) {
                    strIdx++;
                    offset = 0;
                }
            }
            if (tok == '\0')
                break;
        }
    }

    int saveStr(unsigned char* str, unsigned char* arr)
    {
        unsigned char tempStr[5] = {};
        transTo5ByteStr(tempStr, str, arr);
        int idx = getIdx(tempStr, arr);

        if (idx != -1)
            return idx;

        int strIdx = 0;
        int offset = 0;

        for (int i = 0; i < 5; i++)
            myDic[dwp][i] = tempStr[i];

        dwp++;
        return dwp - 1;
    }
    unsigned char myDic[MAX_DIC][5];
    unsigned char src[SIZE];
};


int encode(char* src, char* paper, int papern)
{
    unsigned char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0', ' ' };
    for (register int i = 0; i < papern; i++)
        src[i] = 0;

    Data* data = (Data*)src;
    data->dwp = 0;
    data->srcSize = 0;

    unsigned char str[8];
    int wp = 0;
    int myDicIdx = 0;
    int srcIdx = 0;
    int offset = 0;

    for (register int i = 0; i < papern; i++) {
        if (paper[i] == ' ') {

            str[wp] = '\0';
            myDicIdx = data->saveStr(str, arr);

            for (int shift = 9; shift >= 0; shift--) {
                int bit = myDicIdx >> shift;
                data->src[srcIdx] |= bit << (7 - offset);
                offset++;

                if (offset == 8) {
                    srcIdx++;
                    offset = 0;
                }
            }
            wp = 0;
            continue;
        }
        str[wp++] = paper[i];
    }
    data->srcSize = srcIdx + 1;

    int size = 4430 + data->srcSize;
    return size;
}

void decode(char* dest, char* src, int s)
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0', ' ' };
    Data* data = (Data*)src;
    int tempIdx = 0;
    int srcIdx = 0;
    int offset = 0;
    int destIdx = 0;
    char tempStr[8] = {};

    while (1) {
        tempIdx = 0;

        for (int i = 9; i >= 0; i--) {
            int bit = (data->src[srcIdx] >> (7 - offset++)) & 1;

            if (offset == 8) {
                srcIdx++;
                offset = 0;
            }
            tempIdx |= bit << i;
        }

        if (srcIdx > data->srcSize - 1 || destIdx > 65535)
            break;

        data->transTo8ByteStr(tempIdx, tempStr, arr);

        for (int i = 0; i < 8; i++) {
            if (tempStr[i] == '\0') {
                dest[destIdx++] = ' ';
                break;
            }
            dest[destIdx++] = tempStr[i];
        }
    }
}
#endif