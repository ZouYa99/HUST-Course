#include <stdio.h>
#include <stdlib.h>
int isChinese(char );
int main()
{
 char s[500];
 float a,b,c;/*a统计字数，b统计字符数，c统计行数*/
 a=0;b=0;c=0;
 int i=0,n=0;
 for(s[0]=getchar();s[i]!=EOF;i++) s[i+1]=getchar();
 for(;n<i;n++){
 if(isChinese(s[n])==1){
    a+=0.5; b+=0.5;continue;
 }
 if(s[n]>='!'&&s[n]<='~'){
    if(s[n+1]==' '||s[n+1]=='\r'||s[n+1]=='\t') {a++;b++;n+=2;continue;}
    else if(isChinese(s[n+1])==1){
    a+=0.5; b+=1.5; n++;continue;}
    else if(s[n+1]>='!'&&s[n+1]<='~') {b+=2;n++;continue;}
    }
 if(s[n]=='\n') c++;
 }
 printf("%.0f %.0f %.0f",a,b,c);
return 0;
}
int isChinese(char x)
{
   if((x&0x8080)==0x8080) return 1;
   else return 0;
}
