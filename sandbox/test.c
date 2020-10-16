#include <stdio.h>

int test (const int t) 
{
    t = 1;    
    return t;
}

int main()
{
    test(1);
    return 0;
}