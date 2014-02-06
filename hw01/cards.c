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

/*
   Input card_name from user.
   Input is truncated to the size of definition of card_name in caller.

   Return 1 only if card_name is 'x'.

   message: message to show
   card_name: pointer of character array where input is stored
 */
int input(char *message, char *card_name)
{
    puts(message);
    scanf("%2s", card_name);
    if (card_name[0] == 'x') {
        return 1;
    }
    return 0;
}

/*
   Set val from given card_name.
   This function converts card_name to the value and sets this to val.

   Return 1 if given value is not available to convert.

   card_name: card name to convert
   val: buffer where converted value from card_name is written
 */
int set_value(char *card_name, int *val)
{
    int v = 0;
    switch (card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
        v = 10;
        break;
    case 'A':
        v = 11;
        break;
    case 'X':
        return 1;
        break;
    default:
        v = atoi(card_name);
        if ((v < 1) || (v > 10)) {
            puts("I don't understand that value!");
            return 1;
        }
        break;
    }
    *val = v;
    return 0;
}

/*
   Set count based on given card value.

   val: card value
   count: pointer of integer variable, it is changed
 */
void change_count(int val, int *count)
{
    if ((val > 2) && (val < 7)) {
        ++(*count);
    }
    else if (val == 10) {
        --(*count);
    }
    printf("Current count: %i\n", *count);
}

/*
   Main process function.
 */
void process()
{
    char card_name[3];
    int count = 0, val = 0;
    
    while (1) {
        if (input("Enter the card_name: ", card_name) != 0) {
            break;
        }
        if (set_value(card_name, &val) != 0) {
            continue;
        }
        change_count(val, &count);
    }
}

int main()
{
    process();
    return 0;
}
