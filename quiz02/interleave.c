#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *interleave(char *s1, char *s2)
{
    int i, j;
    int what = 0;   // 0 for s1, 1 for s2
    char *res = malloc(strlen(s1) + strlen(s2) + 1);

    printf("Enter\n");
    for (i = 0; i < strlen(s1) + strlen(s2) + 1; ++i) {
        res[i] = 0;
    }

    for (i = 0, j = 0; ; ) {
        printf("i = %d\n", i);
        if (what == 0) {
            printf("%c\n", s1[i]);
            res[i + j] = s1[i];
            if (i != strlen(s1)) {
                ++i;
            }
            if (j == strlen(s2)) {
                what = 0;
            }
            else {
                what = 1;
            }
        }
        else {
            printf("%c\n", s2[i]);
            res[i + j] = s2[j];
            if (j != strlen(s2)) {
                ++j;
            }
            if (i == strlen(s1)) {
                what = 1;
            }
            else {
                what = 0;
            }
        }
        if (i == strlen(s1) && j == strlen(s2)) {
            break;
        }
    }
    return res;
}

void main()
{
    printf("[%s], [%s] = [%s]\n", "clips", "aloe", interleave("clips", "aloe"));
    printf("[%s], [%s] = [%s]\n", "a", "lot", interleave("a", "lot"));
}
