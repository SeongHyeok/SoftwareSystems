/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(...)
#endif

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
// strcat
char *strjoin(char *array[], int n)
{
    int i, size = 0;
    char *buf;

    // calculate full size
    for (i = 0; i < n; ++i) {
        size += strlen(array[i]);
        //DEBUG_PRINT("%d / size: %d\n", i, size);
    }

    buf = malloc(sizeof(char) * (size + 1));
    memset(buf, '\0', size + 1);

    for (i = 0; i < n; ++i) {
        strcat(buf, array[i]);
        DEBUG_PRINT("%d / %s\n", i, buf);
    }

    return buf;
}

// strcpy
char *strjoin2(char *array[], int n)
{
    int i, size = 0;
    char *buf;

    // calculate full size
    for (i = 0; i < n; ++i) {
        size += strlen(array[i]);
        //DEBUG_PRINT("%d / size: %d\n", i, size);
    }

    buf = malloc(sizeof(char) * (size + 1));
    memset(buf, '\0', size + 1);

    size = 0;
    for (i = 0; i < n; ++i) {
        strcpy((buf + size), array[i]);
        size += strlen(array[i]);
        DEBUG_PRINT("%d / %s\n", i, buf);
    }

    return buf;
}

int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("strcat / %s\n", s);
    printf("strcpy / %s\n", strjoin2(tracks, 5));
    return 0;
}
