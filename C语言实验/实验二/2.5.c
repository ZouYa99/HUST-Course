#include <stdio.h>
#include <stdlib.h>

int main()
{
   char s[50];
   int i;
   scanf("%s",s);
   if(s[0]=='1'){
    if(s[1]=='3'||s[1]=='4'||s[1]=='5'||s[1]=='7'||s[1]=='8')
    {
        for(i=2;s[i]!='\0'&&(s[i]>='0'&&s[i]<='9');)
            ++i;
         if(i==11)
            printf("%s is a telephone number",s);
            else printf("no");
    }
   }

return 0;

}
