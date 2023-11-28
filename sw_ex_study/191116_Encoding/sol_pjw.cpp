//SCORE: 3902045.00400 박종환 
//bit단위로 잘라서 저장했는데, 접근 방식이 잘못되었나 봅니다.스코어가 높네요.

#if 0
int min(int a, int b)
{
    if (a < b) { return a; }
    return b;
}


int encode(char* src, char* paper, int papern)
{
    char alphabet[27] = {
        ' ', 'e', 't', 'a', 'o', 'n', 's', 'h', 'r', 'd',
        'l', 'i', 'c', 'u', 'm', 'w', 'f', 'g', 'y',
        'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'
    };

    int charIdx[256];
    charIdx[' '] = 0;

    for (int i = 1; i < 27; i++)
    {
        charIdx[alphabet[i]] = i;
    }

    int bitCount[27] = { 1, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 10, 13, 13, 13, 13, 13 };
    int bitNum[27] = {
        0, 8, 9, 10, 11, 12, 13, 14,
        120, 121, 122, 123, 124, 125, 126,
        1016, 1017, 1018, 1019, 1020, 1021, 1022,
        8184, 8185, 8186, 8187, 8188
    };

    int bitMask[9] = {
        0b00000000,
        0b00000001,
        0b00000011,
        0b00000111,
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111111,
        0b11111111
    };
    int bitSum = 0;

    for (int i = 0; i <= papern; i++)
    {
        int remain = 8 - (bitSum % 8);
        int cnt;
        int buf;
        int piece = 0;

        if (i == papern)
        {
            cnt = 13; buf = 8190;
        }
        else {
            cnt = bitCount[charIdx[paper[i]]];
            buf = bitNum[charIdx[paper[i]]];
        }

        while (remain < cnt)
        {
            int cutMask = ~(bitMask[remain] << (cnt - remain));
            piece = ((buf >> (cnt - remain)) & bitMask[remain]);
            src[bitSum >> 3] <<= remain;
            src[bitSum >> 3] |= piece;
            bitSum += remain;
            cnt -= remain;
            remain = 8 - (bitSum % 8);
            buf &= cutMask;
        }
        src[bitSum >> 3] <<= cnt;
        src[bitSum >> 3] |= buf;
        bitSum += cnt;
    }
    int remain = 8 - (bitSum % 8);
    src[bitSum >> 3] <<= remain;
    return (bitSum >> 3) + 1;
}


void decode(char* dest, char* src, int s)
{
    int bitNum[27] = {
        0, 8, 9, 10, 11, 12, 13, 14,
        120, 121, 122, 123, 124, 125, 126,
        1016, 1017, 1018, 1019, 1020, 1021, 1022,
        8184, 8185, 8186, 8187, 8188
    };

    char alphabet[27] = {
        ' ', 'e', 't', 'a', 'o', 'n', 's', 'h', 'r', 'd',
        'l', 'i', 'c', 'u', 'm', 'w', 'f', 'g', 'y',
        'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'
    };
    char hashChar[9000];

    for (int i = 0; i < 27; i++)
    {
        hashChar[bitNum[i]] = alphabet[i];
    }

    int bitMask[9] = {
        0b00000000,
        0b00000001,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b10000000
    };

    int bitSum = 0;
    int buf;
    int k = 0;

    while (true)
    {
        if ((src[bitSum >> 3] & bitMask[8 - (bitSum % 8)]) == 0)
        {
            dest[k++] = ' ';
            bitSum++;
            continue;
        }
        buf = 1; bitSum++;
        int remain;

        while (buf == 1 || (buf & 0b111) == 0b111)
        {
            int mask = 0;
            int cnt = 3;
            remain = 8 - (bitSum % 8);

            if (remain < cnt)
            {
                for (int b = 0; b < remain; b++)
                {
                    mask |= bitMask[remain - b];
                }
                buf <<= remain;
                buf |= (mask & src[bitSum >> 3]);
                bitSum += remain;
                cnt -= remain;
            }
            remain = 8 - (bitSum % 8);
            mask = 0;

            for (int b = 0; b < cnt; b++)
            {
                mask |= bitMask[remain - b];
            }

            buf <<= cnt;
            buf |= ((mask & src[bitSum >> 3]) >> (remain - cnt));
            bitSum += cnt;
        }
        if (buf == 8190)
            break;
        char newChar = hashChar[buf];
        dest[k++] = newChar;
    }
}
#endif