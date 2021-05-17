#include <stdio.h>
#include <stdlib.h>
void strReverse(char s[]);
int strLength(char s[]);

int main()
{
   char s[1000];
   printf("input a string\n");
   scanf("%s",s);
   printf("string %s 's length is:%d\n",s,strLength(s));
   strReverse(s);
   printf("reversal:%s",s);
   return 0;
}

int strLength(char s[])
{
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}
void strReverse(char s[])
{
    int i,j;
    for(i=0,j=strLength(s);i<j;i++,j--)
    {
        char t;
        t=s[i]; s[i]=s[j-1]; s[j-1]=t;
    }
}
