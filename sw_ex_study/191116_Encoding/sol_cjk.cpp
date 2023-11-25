// SCORE: 1977288.01025 ÃÖÁØ°æ 2023.11.21

#if 1
inline int max(int a, int b) { return a > b ? a : b; }
inline int abs(int a) { return a < 0 ? a * -1 : a; }

struct String
{
    char data[1024][8];
    char dataLen[1024];
    int dataCnt;
    int LUT[130] = {
          0,0,0,0,0,0,0,0,0,0,//0~9
          0,0,0,0,0,0,0,0,0,0,//10~19
          0,0,0,0,0,0,0,0,0,0,//20~29
          0,0,27,0,0,0,0,0,0,0,//30~39
          0,0,0,0,0,0,0,0,0,0,//40~49
          0,0,0,0,0,0,0,0,0,0,//50~59
          0,0,0,0,0,0,0,0,0,0,//60~69
          0,0,0,0,0,0,0,0,0,0,//70~79
          0,0,0,0,0,0,0,0,0,0,//80~89
          0,0,0,0,0,0,0,0,1,2,//90~99
          3,4,5,6,7,8,9,10,11,12,//100~109
          13,14,15,16,17,18,19,20,21,22,//110~119
          23,24,25,26//120~123
    };

    void init()
    {
        for (int i = 0; i < 1024; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                data[i][j] = 0;
            }
            dataLen[i] = 0;
        }
        dataCnt = 0;
    }

    int strcmp(char* str1, int len1, char* str2, int len2)
    {
        int maxLen = max(len1, len2);

        for (int i = 0; i < maxLen; i++)
        {
            if (str1[i] != str2[i])
                return 0;
        }
        return 1;
    }

    unsigned long long StringAdd(char* str, int len)
    {
        unsigned long long DataTemp = 0;
        DataTemp |= (len & 0x07);

        for (int i = 0; i < len; i++)
        {
            DataTemp <<= 5;
            data[dataCnt][i] = str[i];
            DataTemp |= (LUT[str[i]] & 0x1f);
        }
        dataLen[dataCnt++] = len;
        return DataTemp;
    }

    int GetString2Idx(char* str, int len)
    {
        for (int i = 0; i < dataCnt; i++)
        {
            if (strcmp(data[i], dataLen[i], str, len))
                return i;
        }
        return -1;
    }

    void GetIdx2String(int idx, char* str, int& strLen)
    {
        strLen = dataLen[idx];
        for (int i = 0; i < strLen; i++)
        {
            str[i] = data[idx][i];
        }
    }
};


int encode(char* src, char* paper, int papern)
{
    for (int i = 0; i < papern; i++)
    {
        src[i] = 0;
    }
    String string;
    string.init();

    unsigned long long* pSrc = (unsigned long long*)src;
    int wp = 0;
    int srcCnt = 0;
    int shift = 64;

    while (wp < papern)
    {
        char sTemp[8] = { 0 };
        int TempLen = 0;

        while (paper[wp] != ' ')
        {
            sTemp[TempLen++] = paper[wp++];
        }
        wp++;
        int idx = string.GetString2Idx(sTemp, TempLen);
        unsigned long long data;

        if (shift == 0)
        {
            shift = 64;
            srcCnt++;
        }

        int dataLen;
        shift -= 1;

        if (idx == -1)
        {
            data = string.StringAdd(sTemp, TempLen);
            dataLen = TempLen * 5 + 3;
            pSrc[srcCnt] |= 1ULL << shift;
        }
        else
        {
            data = idx;
            dataLen = 10;
        }
        shift -= dataLen;

        if (shift < 0)
        {
            shift = abs(shift);
            pSrc[srcCnt++] |= (data >> shift);
            shift = 64 - shift;
        }
        pSrc[srcCnt] |= (data << shift);
    }
    return (srcCnt + 1) * 8;
}


void decode(char* dest, char* src, int s)
{
    char LUT[33] = { "abcdefghijklmnopqrstuvwxyz" };
    String string;

    string.init();
    unsigned long long* pSrc = (unsigned long long*) src;
    int dataLen = s / 8;
    int shift = 64;
    int destCnt = 0;
    int srcCnt = 0;

    while (dataLen > srcCnt)
    {
        if (shift == 0)
        {
            shift = 64;
            srcCnt++;
        }

        shift -= 1;
        unsigned long long data = 0;
        char strTemp[8] = { 0 };
        int strLen = 0;

        if (pSrc[srcCnt] & (1ULL << shift))
        {
            shift -= 3;
            if (shift < 0)
            {
                shift = abs(shift);
                data |= (pSrc[srcCnt++] << shift) & 0x07;
                shift = 64 - shift;
            }
            data |= (pSrc[srcCnt] >> shift) & 0x07;
            strLen = (int)data;

            for (int i = 0; i < strLen; i++)
            {
                shift -= 5;
                data = 0;

                if (shift < 0)
                {
                    shift = abs(shift);
                    data |= (pSrc[srcCnt++] << shift) & 0x1f;
                    shift = 64 - shift;
                }
                data |= (pSrc[srcCnt] >> shift) & 0x1f;
                strTemp[i] = LUT[data];
            }
            string.StringAdd(strTemp, strLen);
        }
        else
        {
            shift -= 10;
            if (shift < 0)
            {
                shift = abs(shift);
                data |= (pSrc[srcCnt++] << shift) & 0x3ff;
                shift = 64 - shift;
            }
            data |= (pSrc[srcCnt] >> shift) & 0x3ff;
            string.GetIdx2String(data, strTemp, strLen);
        }

        if (destCnt + strLen > 65535)
            break;

        for (int i = 0; i < strLen; i++)
        {
            dest[destCnt++] = strTemp[i];
        }
        dest[destCnt++] = ' ';
    }
}
#endif