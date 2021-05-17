#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    c=getchar();
    putchar(c>='A'&&c<='Z'?c-'A'+'a':c);
}
