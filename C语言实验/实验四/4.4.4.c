#include <stdio.h>
#define CHANGE 1
/*CHANGE=1ʱ����任������֣�CHANGE=0ʱ���ԭ��*/
int main()
{
    char c;
    #if CHANGE
    for(c=getchar();c!='\0';c=getchar()){
        if(c>=65&&c<=90) putchar(c-'A'+'a');
        else if(c>=97&&c<=122)putchar(c-'a'+'A');
    }
    #else
    for(c=getchar();c!='\0';c=getchar())putchar(c);
    #endif // CHANGE
    return 0;
}
