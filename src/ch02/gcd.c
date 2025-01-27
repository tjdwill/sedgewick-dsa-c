// gcd.c
#include "gcd.h"
/// Calculate the greatest common divisor between two integers
int gcd(int x, int y)
{
    int larger = 0;
    int smaller = 0;
    if (x > y)
    {
        larger = x;
        smaller = y;
    }
    else
    {
        larger = y;    
        smaller = x;
    }
    int modulo = larger % smaller;
    while (modulo != 0)
    {
        larger = smaller;
        smaller = modulo;
        modulo = larger % smaller;
    }
    return smaller;
}
