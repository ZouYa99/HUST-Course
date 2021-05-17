#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
  int number;
  int front,after;
  int x;
  for(front=1;front<=9;front++){
    for(after=1;after<=9;after++){
        if(front==after) continue;
        number=front*1100+after*11;
        x=sqrt(number);
        if(x*x==number)
         printf("%d",number);
    }
  }
return 0;
}
