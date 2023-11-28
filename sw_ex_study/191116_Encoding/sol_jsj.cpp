// SCORE: 19330723.12976 조수장 2023.11.22

#if 0
#define NOT_EXIST -1

int getCount(char* paper, const int rp, const int papern)
{
	int cnt = 0;
	while (rp + cnt < papern && paper[rp + cnt] != ' ')
		cnt++;
	return cnt;
}

// src의 bIdx에 len개의 비트에 val값을 기록.
void write(bool* bits, int* bwp, int len, int val)
{
	for (int i = 0; i < len; i++)
	{
		bits[*bwp + i] = val & (1 << (len - 1 - i));
	}
	*bwp += len;
}

void write2(char* dest, int* dwp, char* word, int len)
{
	for (int i = 0; i < len; i++)
	{
		dest[*dwp + i] = word[i];
	}
	dest[*dwp + len] = ' ';
	*dwp += (len + 1);
}

// src의 rp부터 len만큼 읽을 때의 값을 반환
// 최우측부터 1을 기준으로 하여 좌측시프트 
int read(bool* bits, int* rp, const int len)
{
	int val = 0;
	for (int i = 0; i < len; i++)
		val += (bits[*rp + i] << len - 1 - i);

	*rp += len;
	return val;
}

int getWordIndex(char words[][8], int wordsLens[], int* wwp, char* paper, int pIdx, int cnt)
{
	int len = *wwp;
	for (int wIdx = 0; wIdx < len; wIdx++)
	{
		if (wordsLens[wIdx] != cnt)
			continue;

		int i = 0;
		for (; i < cnt; i++)
		{
			if (words[wIdx][i] != paper[pIdx + i])
				break;
		}
		if (i == cnt)
			return wIdx;
	}
	return NOT_EXIST;
}

void saveWord(char words[][8], int wordsLens[], int* wwp, char* paper, int pIdx, int cnt)
{
	for (int i = 0; i < cnt; i++)
		words[*wwp][i] = paper[pIdx + i];

	words[*wwp][cnt] = '\0';
	wordsLens[*wwp] = cnt;
	(*wwp)++;
}

int encode(char* src, char* paper, int papern)
{
	// 이전 테케 쓰레기값 제거
	for (int i = 0; i < 65536; i++)
		src[i] = 0;

	char words[1000][8];
	int wordsLens[1000];
	int wwp = 0;         // word write point
	bool bits[65536 * 8];
	int bwp = 0;         // bit write point

	for (int prp = 0; prp < papern;) // paper read point
	{
		// 글자라면 바로 기록
		int cnt = getCount(paper, prp, papern);
		if (cnt == 1)
		{
			// 등록여부(1bit) + (단어길이 3bit[2 ~ 7])를 위한 4bit활용.
			write(bits, &bwp, 4, 1);
			write(bits, &bwp, 5, paper[prp] - 'a');
			prp += (cnt + 1);
			continue;
		}

		// 사전에 등록된 단어라면 인덱스로 기록
		int wIdx = getWordIndex(words, wordsLens, &wwp, paper, prp, cnt);
		if (wIdx != NOT_EXIST)
		{
			write(bits, &bwp, 1, 1);
			write(bits, &bwp, 10, wIdx);
			prp += (cnt + 1);
			continue;
		}

		// 사전에 등록된 단어가 아니라면 길이, 단어 전달, 단어 저장.
		saveWord(words, wordsLens, &wwp, paper, prp, cnt);
		write(bits, &bwp, 4, cnt);

		for (int i = 0; i < cnt; i++)
			write(bits, &bwp, 5, paper[prp + i] - 'a');

		prp += (cnt + 1);
	}

	write(bits, &bwp, 1, 1);
	write(bits, &bwp, 10, 1023);
	bwp += (8 - (bwp % 8));

	for (int bIdx = 0; bIdx < bwp; bIdx++)
	{
		src[bIdx >> 3] = src[bIdx >> 3] | (bits[bIdx] << (7 - (bIdx % 8)));
	}
	return (bwp / 8);
}


void decode(char* dest, char* src, int s)
{
	int dwp = 0;    // dest write point
	// bit형태로 복사
	bool bits[65536 * 8];

	for (int i = 0; i < s * 8; i++)
	{
		bits[i] = src[i / 8] & (1 << (7 - (i % 8)));
	}

	int wordLens[1000];
	char words[1000][8];
	int wwp = 0;      // word write point

	for (int rp = 0; rp < s * 8; )
	{
		// 첫 값이 있다면, 10bit를 읽은 후 불러온 단어를 그대로 기록한다.
		int firstValue = read(bits, &rp, 1);
		if (firstValue == 1)
		{
			int wIdx = read(bits, &rp, 10);
			if (wIdx == 1023)
			{
				break;
			}

			// wIdx가 가리키는 단어로 복구.
			write2(dest, &dwp, words[wIdx], wordLens[wIdx]);
			continue;
		}
		// 단글자라면 한개분(5bit)를 읽어서 바로 복구
		int len = read(bits, &rp, 3);

		if (len == 1)
		{
			int ch = read(bits, &rp, 5);
			char temp[2];
			temp[0] = 'a' + ch;
			temp[1] = '\0';

			write2(dest, &dwp, temp, 1);
			continue;
		}

		// 새로 등장하는 단어라면 길이만큼 읽어서 등록 + 복구.
		for (int i = 0; i < len; i++)
		{
			int ch = read(bits, &rp, 5);
			words[wwp][i] = 'a' + ch;
			wordLens[wwp] = len;
		}
		words[wwp][len] = '\0';
		write2(dest, &dwp, words[wwp], wordLens[wwp]);
		wwp++;
	}
}
#endif