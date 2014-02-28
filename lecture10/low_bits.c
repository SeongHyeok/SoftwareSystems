#include <stdio.h>

/*
 * low_bits()
 *
 * takes a byte and a number of bits, n, 
 * and returns a byte that contains only the n right-most bits of the bytes.
 *
 */
char low_bits(char byte, int n)
{
    int mask = 1;
    mask = (mask << n) - 1;
    //printf("mask: %d\n", mask);
    return (byte & mask);

    // Exactly same as Allen's, yay! 
}

/*
 *
 *
 *
 */
int negate(int x)
{
    // 1. Mine
    //unsigned int mask = 0xFFFFFFFF;
    // Allen: 
    //  we don't know the sizes of int, 
    //  we can use it only if size of int is fixed
    
    // 2. Allen's
    //int mask = -1;

    // 3. Bitwise negative
    int mask = ~0;
    return (x ^ mask) + 1;
}

int main()
{
    printf("low_bits(63, 4): %d\n", low_bits(63 ,4));
    printf("low_bits(3, 1): %d\n", low_bits(3 ,1));
    printf("low_bits(7, 2): %d\n", low_bits(7 ,2));
    printf("low_bits(7, 4): %d\n", low_bits(7 ,4));
    printf("low_bits(127, 5): %d\n", low_bits(127 ,5));
    printf("low_bits(127, 6): %d\n", low_bits(127 ,6));
    printf("low_bits(14, 1): %d\n", low_bits(14 ,1));
    printf("negate of 10 is %d\n", negate(10));
    return 0;
}
