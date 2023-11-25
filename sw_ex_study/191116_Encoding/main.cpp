#include <stdio.h>
#include <memory.h>
#include <time.h>

extern int encode(char*, char*, int);
extern void decode(char*, char*, int);

static unsigned long long seed = 5; // seed can be changed

static unsigned int random(void) {
    return ((unsigned int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

static int  hit[26] = { 82, 15, 28, 43, 127, 22, 20, 61, 30, 2, 8, 40, 24, 67, 75, 19, 1, 60, 63, 91, 28, 10, 24, 2, 20, 1 };

//static char dummy1[9999];
//static char dummy2[9998];
//static char dummy3[9997];
//static char dummy4[2182];
//static char dummy5[291];

static char alpha[963];         // 문자들 a 26 + b 15 + ... + z 1 (전체 963개)
static char dic[1024][8];       // 단어장에서 각 단어
static int  dics[1024];         // 단어장에서 각 단어의 길이 저장 (최대 7)

static int  papern;             // 문서의 크기
static char src[65536];         // 인코딩된 문서
static char dest[65536];        // 디코딩된 문서

static char paper[65536];       // 문서
static char bak_paper[65536];   // 문서 복사본


static void build_dic(void)
{
    int i = 0;
    int j = 0;

    // 문자
    for (int c = 0; c < 963; c++) {
        if (j >= hit[i]) {
            i++;
            j = 0;
        }
        alpha[c] = 'a' + i;
        j++;
    }

    // 단어장 1024
    for (int c = 0; c < 1024; c++) {
        int l = 1 + random() % 7;   // 단어 길이
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

    // 테스트 케이스 100개
    for (int c = 0; c < 100; c++)
    {
        int pl = 0;

        while (true) {
            int i = random() % 1024;            // 1024개 단어중 랜점 선택
            if (pl + dics[i] > 65535) break;    // 최대 문서 크기 65535 byte

            for (int c = 0; c < dics[i]; c++)   // 선택한 단어
                paper[pl++] = dic[i][c];

            paper[pl++] = ' ';                  // 단어끝에 빈칸 삽입
        }
        papern = pl;                            // 문서 크기

        // 인코딩
        for (int i = 0; i < papern; i++) { bak_paper[i] = paper[i]; }
        int s = encode(src, bak_paper, papern);
        for (int i = s; i < 65536; i++) { src[i] = 0; }

        // 디코딩
        decode(dest, src, s);
        if (memcmp(paper, dest, papern) != 0) { RATE += 10000000; } // 패널티
        else { RATE += s; }                             // 인코딩된 용량 (byte)를 더한다
    }

    TIME = clock() - TIME;
    printf("SCORE: %.5f\n", RATE + TIME / 100000.);

}