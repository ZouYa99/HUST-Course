#include <stdio.h>
#include <stdlib.h>

int isperfect(int x)
{
    int y,s;
    for(s=0,y=1;y<=x/2;y++)
    {
        if(!(x%y))
            s+=y;
    }
    if(s==x)
        return 1;
    else
        return 0;
}

int main()
{
    int a;
    printf("within 1000 the perfect have:");
    for(a=1;a<=1000;a++)
        if(isperfect(a))
          printf("%8d",a);
    return 0;
}
