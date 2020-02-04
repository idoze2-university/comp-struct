#include <stdlib.h>
#include <stdio.h>
int calc(int *x)
{
    return (x ? *x : 0);
}
int main()
{
    int x = 4;
    printf("%d\n", calc(5));
    return 0;
}
