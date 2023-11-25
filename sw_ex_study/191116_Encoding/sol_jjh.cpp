#if 0
// 1883081.00886 조지훈 2023.11.22
int strcmp(char* s1, char* s2)
{
	while (*s1 && *s2) {
		if (*s1++ != *s2++) {
			return 1;
		}
	}

	if (*s1 || *s2) {
		return 1;
	}

	return 0;
}

int strcpy(char* src, char* dest)
{
	int i = 0;
	while (src[i]) {
		dest[i++] = src[i];
	}
	dest[i] = 0;
	return i;
}

struct HuffmanCode
{
	short bits;
	char len;
};

struct HuffmanDecode
{
	char bits[9];
	char len;
};

void initHuffmanCode(HuffmanCode* huffman)
{
	huffman['d'] = { 0b0000, 4 };
	huffman['f'] = { 0b00010, 5 };
	huffman['m'] = { 0b00011, 5 };
	huffman['t'] = { 0b001, 3 };
	huffman['q'] = { 0b010000000, 9 };
	huffman['z'] = { 0b010000001, 9 };
	huffman['j'] = { 0b010000010, 9 };
	huffman['x'] = { 0b010000011, 9 };
	huffman['k'] = { 0b0100001,7 };
	huffman['v'] = { 0b010001,6 };
	huffman['u'] = { 0b01001,5 };
	huffman['w'] = { 0b01010,5 };
	huffman['c'] = { 0b01011,5 };
	huffman['r'] = { 0b0110,4 };
	huffman['h'] = { 0b0111,4 };
	huffman['s'] = { 0b1000,4 };
	huffman['i'] = { 0b10010,5 };
	huffman['b'] = { 0b100110,6 };
	huffman['p'] = { 0b100111,6 };
	huffman['e'] = { 0b101,3 };
	huffman['l'] = { 0b11000,5 };
	huffman['g'] = { 0b110010,6 };
	huffman['y'] = { 0b110011,6 };
	huffman['a'] = { 0b1101,4 };
	huffman['n'] = { 0b1110,4 };
	huffman['o'] = { 0b1111,4 };
}


void initHuffmanDecode(HuffmanDecode* huffman)
{
	huffman['d'] = { {0,0,0,0}, 4 };
	huffman['f'] = { {0,0,0,1,0}, 5 };
	huffman['m'] = { {0,0,0,1,1}, 5 };
	huffman['t'] = { {0,0,1}, 3 };
	huffman['q'] = { {0,1,0,0,0,0,0,0,0}, 9 };
	huffman['z'] = { {0,1,0,0,0,0,0,0,1}, 9 };
	huffman['j'] = { {0,1,0,0,0,0,0,1,0}, 9 };
	huffman['x'] = { {0,1,0,0,0,0,0,1,1}, 9 };
	huffman['k'] = { {0,1,0,0,0,0,1},7 };
	huffman['v'] = { {0,1,0,0,0,1},6 };
	huffman['u'] = { {0,1,0,0,1},5 };
	huffman['w'] = { {0,1,0,1,0},5 };
	huffman['c'] = { {0,1,0,1,1},5 };
	huffman['r'] = { {0,1,1,0},4 };
	huffman['h'] = { {0,1,1,1},4 };
	huffman['s'] = { {1,0,0,0},4 };
	huffman['i'] = { {1,0,0,1,0},5 };
	huffman['b'] = { {1,0,0,1,1,0},6 };
	huffman['p'] = { {1,0,0,1,1,1},6 };
	huffman['e'] = { {1,0,1},3 };
	huffman['l'] = { {1,1,0,0,0},5 };
	huffman['g'] = { {1,1,0,0,1,0},6 };
	huffman['y'] = { {1,1,0,0,1,1},6 };
	huffman['a'] = { {1,1,0,1},4 };
	huffman['n'] = { {1,1,1,0},4 };
	huffman['o'] = { {1,1,1,1},4 };
}

int encode(char* src, char* paper, int papern)
{
	HuffmanCode huffman[256];

	char dic[1024][8];
	int dLen[1024];
	int d = 0;

	short int code[65535 / 2];
	int c = 0;

	initHuffmanCode(huffman);

	char* word = paper;
	for (int i = 0; i < papern; i++)
	{
		src[i] = 0;

		if (paper[i] != ' ') continue;

		paper[i] = 0;

		int found = -1;
		int len;

		for (int j = 0; j < d; j++)
		{
			if (strcmp(dic[j], word) == 0) {
				found = j;
				len = dLen[found];
				break;
			}
		}

		if (found == -1) {
			len = dLen[d] = strcpy(word, dic[d]);
			found = d++;
		}

		word += len + 1;

		code[c++] = found;

	}

	for (int i = papern; i < 65535; i++)
	{
		src[i] = 0;
	}

	int b = 0;

	// 단어집 저장
	for (int i = 0; i < d; i++)
	{
		// 단어 길이
		for (int j = 0; j < 3; j++)
		{
			int bit = (dLen[i] >> (2 - j)) & 0x01;
			src[b++ / 8] |= bit << (7 - b % 8);
		}

		for (int j = 0; j < dLen[i]; j++)
		{
			char ch = dic[i][j];
			int len = huffman[ch].len;
			int bits = huffman[ch].bits;

			for (int k = 0; k < len; k++)
			{
				int bit = (bits >> (len - 1 - k)) & 0x01;
				src[b++ / 8] |= bit << (7 - b % 8);
			}
		}
	}

	b += 3;

	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int bit = (code[i] >> (9 - j)) & 0x01;
			src[b++ / 8] |= bit << (7 - b % 8);
		}
	}

	int bytes = b / 8 + (b % 8 == 0 ? 0 : 1);
	return bytes;
}

void decode(char* dest, char* src, int s)
{
	HuffmanDecode huffman[256];

	initHuffmanDecode(huffman);

	int range = s * 8;

	char dic[1024][8];
	int dLen[1024];
	int d = 0;


	int b = 0;
	while (b + 5 < range)
	{
		int& len = dLen[d] = 0;
		for (int j = 0; j < 3; j++)
		{
			int bit = (src[b++ / 8] >> (7 - b % 8)) & 0x01;
			len |= bit << (2 - j);
		}

		if (len == 0)
			break;

		for (int i = 0; i < len; i++)
		{
			char& ch = dic[d][i] = 0;

			int bits[9];
			for (int j = 0; j < 2; j++)
			{
				int bit = (src[b++ / 8] >> (7 - b % 8)) & 0x01;
				bits[j] = bit;
			}

			for (int j = 2; j < 9; j++)
			{
				int bit = (src[b++ / 8] >> (7 - b % 8)) & 0x01;
				bits[j] = bit;

				for (char k = 'a'; k <= 'z'; k++)
				{
					if (huffman[k].len != j + 1)
						continue;

					bool match = true;

					for (int m = 0; m < huffman[k].len; m++)
					{
						if (huffman[k].bits[m] != bits[m]) {
							match = false;
							break;
						}
					}

					if (match == true) {
						ch = k;
						break;
					}
				}

				if (ch != 0)
					break;
			}
		}
		dic[d++][len] = 0;
	}

	char* word = dest;
	while (b + 10 <= range)
	{
		int code = 0;
		for (int j = 0; j < 10; j++)
		{
			int bit = (src[b++ / 8] >> (7 - b % 8)) & 0x01;
			code |= bit << (9 - j);
		}

		int len = strcpy(dic[code], word);

		word[len] = ' ';
		word += len + 1;
	}
}
#endif