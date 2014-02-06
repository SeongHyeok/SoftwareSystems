/*
 * Card Counting Program
 *  based on page 37 in Head First C
 *
 * Author: SeongHyeok Im (ishez9210@gmail.com)
 * Date: Feb 5 2014
 *
 */

#include <stdio.h>
#include <stdlib.h>

int input(char *card_name)
{
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
    if (card_name[0] == 'x') {
        return 1;
    }
    return 0;
}

int get_value(char *card_name, int *ret)
{
    int val = 0;
    switch (card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
        val = 10;
        break;
    case 'A':
        val = 11;
        break;
    case 'X':
        return 1;
        break;
    default:
        val = atoi(card_name);
        if ((val < 1) || (val > 10)) {
            puts("I don't understand that value!");
            return 1;
        }
        break;
    }
    *ret = val;
    return 0;
}

void process()
{
    char card_name[3];
    int count = 0, val = 0;
    while (input(card_name) == 0) {
        if (get_value(card_name, &val) != 0) {
            continue;
        }
        
        if ((val > 2) && (val < 7)) {
            count++;
        }
        else if (val == 10) {
            count--;
        }

        printf("Current count: %i\n", count);
    } //while
}

int main()
{
    process();
    return 0;
}
