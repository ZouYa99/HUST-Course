#include <stdio.h>
#include <stdlib.h>


int main(void)
{
char c,numchar,numline;
numchar=0;
numline=0;
printf("input several lines of text,Ctrl+z finish\n");
while((c=getchar())!=EOF)
{
    numchar++;
    if(c=='\n')
        numline++;
}
printf("char number:%d,",numchar);
printf("line number:%d\n",numline);
return 0;
}
