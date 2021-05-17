#include <stdio.h>
#include <stdlib.h>

int main()
{
  int s[15];
  int i=0,t=0,n=0,number=0,k=0,f=0,g=0;
  int m[4];
  int judge=1;
  unsigned int IP;
  char ch;
  for(ch=getchar();ch!='\n';ch=getchar(),++i){
        if(!(ch>='0'&&ch<='9')&&ch!='.') {printf("NO");break;judge=0;}
        if(ch>='0'&&ch<='9') s[i]=ch-'0';
        if(ch=='.') {t++;
        s[i]=10;}
  }
  s[i]=10;
  if(judge==1&&t==3){
   start:
   for(;s[n]!=10;n++) number++;
   if(number>=1&&number<=3){
    switch(number){
    case 1:m[k]=s[n-1];break;
    case 2:m[k]=s[n-2]*10+s[n-1];break;
    case 3:m[k]=s[n-3]*100+s[n-2]*10+s[n-1];break;}
    number=0;k++;n++;
    if(k<=3) goto start;
   }
   else {printf("NO");judge=0;}
  }
  else printf("NO");
  if(judge!=0){
    for(;f<=3;f++){
        if(m[f]>=0&&m[f]<=255) g++;
    }
    if(g==4){
        printf("YES\n");
        IP=((m[0]<<24)&0xff000000)|((m[1]<<16)&0x00ff0000)|((m[2]<<8)&0x0000ff00)|m[3];
        printf("%u",IP);
    }
  }
return 0;
}
