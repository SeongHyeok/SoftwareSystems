/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	    if (strstr(tracks[i], search_for)) {
	        printf("Track %i: '%s'\n", i, tracks[i]);
	    }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
/*
 * Regular Expression Resources I refered.
 *
 * : http://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples
 * : http://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html
 * : http://pic.dhe.ibm.com/infocenter/iseries/v7r1m0/index.jsp?topic=%2Frtref%2Fregerror.htm
 *
 */
void find_track_regex(char pattern[])
{
    regex_t regex;
    int ret, i;
    char buf[128];
    
    // Compile regular expression
    ret = regcomp(&regex, pattern, 0);
    if (ret != 0) {
        // Convert error code to error message
        regerror(ret, &regex, buf, 128);
        printf("Error on regcomp(), error message: %s\n", buf);
        exit(1);
    }
    
    for (i = 0; i < NUM_TRACKS; ++i) {
        // Execute regular expression
        if (regexec(&regex, tracks[i], 0, NULL, 0) != REG_NOMATCH) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
    
    regfree(&regex);
    return;
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	    *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    //find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
