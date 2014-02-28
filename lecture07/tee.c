#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // optarg
#include <string.h> // memcpy

#define FILE_NAME_MAX_LEN   (256)

int main(int argc, char *argv[])
{
    char file_name[FILE_NAME_MAX_LEN];
    FILE *fin, *fout;
    int opt;
    while ((opt = getopt(argc, argv, "a:i")) != -1) {
        printf("opt: %c\n", opt);
        switch (opt) {
            case 'a':
                memcpy(file_name, optarg, 255);
                break;
            case 'i':
                break;
            default:
                break;
        }
    }

    fread(fin, stdin);
    fwrite(
    return 0;
}
