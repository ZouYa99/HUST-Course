#include <stdio.h>
#include <stdlib.h>
int main()
{
  float x,taxx;
  scanf("%f",&x);
  if(x<1000) taxx=0;
  else if(x>=1000&&x<2000) taxx=0.05*(x-1000);
  else if(x>=2000&&x<3000) taxx=0.10*(x-2000)+50;
  else if(x>=3000&&x<4000) taxx=0.15*(x-3000)+150;
  else if(x>=4000&&x<5000) taxx=0.20*(x-4000)+300;
  else if(x>5000) taxx=0.25*(x-5000)+500;
  printf("%f",taxx);
  return 0;
}
