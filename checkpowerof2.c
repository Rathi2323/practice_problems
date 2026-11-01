#include <stdio.h>

int main()
{
    int n=17;
    if(n>0 && (n&(n-1))==0)
    {
        printf("N is a power of 2");
    }
    else printf("N is not a power of 2");
}