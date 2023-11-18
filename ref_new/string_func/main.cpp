#include <cstdio>
#include "strfunc.h"


int main()
{
    char s[] = "123456";
    int x = 123456;

    // sub_str
    printf("%s\n", sub_str(s, 1, 3));

    // str_len
    printf("%d\n", str_len(s));
    printf("%d\n", int_len(x));

    // atoi, itoa
    printf("%d\n", atoi(s));
    printf("%s\n", itoa(x));

    char str[] = "abcd";

    // endcode, decode
    printf("%lld\n", encode(str, 10));
    printf("%s\n", decode(encode(str, 10), 10));

    // strcmp, strcpy, strcat
    char a[20] = "hello";
    char b[20] = "world";
    char c[20];

    printf("strcmp(a, b) = %d\n", strcmp(a, b));
    printf("strcmp(b, a) = %d\n", strcmp(b, a));
    printf("strcmp(a, a) = %d\n", strcmp(a, a));

    strcpy(c, a);
    printf("strcpy(c, a): c = %s\n", c);

    strcat(c, b);
    printf("strcat(c, b): c = %s\n", c);

    return 0;
}