#if 1
#include <cstdio>
#include <cstring>
#include <cmath>

using ull = unsigned long long;

// long long ���� �ִ� 13�ڸ� ���ڿ����� �ؽð� ����
// 27^13 = 4,052,555,153,018,976,267 < 2^62 - 1
// int �� �ִ� 5�ڸ� ���ڿ��� �迭 �ε��� ���� (27^4 = 531,441, 27^5 = 14,348,907)

ull stoull(const char str[], int len) {
    ull hash = 0;
    for (int i = 0; str[i]; i++) { hash = hash * 27 + str[i] - 'a' + 1; }
    for (int i = strlen(str); i < len; i++) { hash *= 27; }    // ������ �񱳽� �ʿ�
    return hash;


}

int main()
{
    int n = 4;
    char s1[] = "ab";
    char s2[] = "azzzzzzzzzzzz";
    char s3[] = "zzzzzzzzzzzzz";

    printf("%4s = %6lld\n", s1, stoull(s1, n));
    printf("%4s = %6lld\n", s2, stoull(s2, n));
    printf("%4s = %6lld\n", s3, stoull(s3, n));

    printf("%lld\n", (ull)pow(27, 13));
    printf("%lld\n", (ull)pow(26, 13));
    printf("%lld\n", (ull)pow(2, 31) - 1);
    printf("%lld\n", (ull)pow(2, 32) - 1);

    // int �� 4�ڸ� �迭 �ε��� ����
    //                        27^4 = 531,441
    //                        27^5 = 14,348,907
    //                        27^6 = 387,420,489
    // int                    27^7 = 1,870,418,611
    // int                2^31 - 1 = 2,147,483,647

    // unsigned long long ���� 13�ڸ� ���ڿ� �ؽð� ����
    // long long             27^13 = 4,052,555,153,018,976,267
    // long long          2^62 - 1 = 4,611,686,018,427,387,903
    // unsigned long long 2^63 - 1 = 9,223,372,036,854,775,807

    int num = 1;
    for (int i = 0; i < 16; i++) {
        num *= 27;
        printf("27^%2d = %d\n", i + 1, num);
    }

    return 0;
}
#endif