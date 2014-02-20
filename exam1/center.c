/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    char *ret;
    int size, left, i;
    
    size = sizeof(char) * (n + 1);
    ret = (char *)malloc(size);
    memset(ret, '\0', size);

    left = (n - strlen(s)) / 2;
    for (i = 0; i < left; ++i) {
        ret[i] = fillchar;
    }
    for (i = left; i < left + strlen(s); ++i) {
        ret[i] = s[i - left];
    }
    for (i = left + strlen(s); i < n; ++i) {
        ret[i] = fillchar;
    }
    return ret;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    char *s5 = center("steven", 10, '#');
    printf("%s\n", s5);

    char *s6 = center("allen", 10, '#');
    printf("%s\n", s6);
    return 0;
}
