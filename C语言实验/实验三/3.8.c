#include <stdio.h>
int main()
{
   char a,b,c,d,e,f,g,h,i,j;
   int x;
   int m,n;
   scanf("%d",&x);
   for(a='0';a<='9';a++)
   {
      for(b='0';b<='9';b++)
      {
          if((b-a)==0) continue;
          for(c='0';c<='9';c++)
          {
              if((b-c)*(c-a)==0) continue;
              for(d='0';d<='9';d++)
              {
                  if((d-c)*(d-a)*(d-b)==0) continue;
                  for(e='0';e<='9';e++)
                  {
                      if((e-c)*(e-a)*(e-b)*(e-d)==0) continue;
                      for(f='0';f<='9';f++)
                      {
                           if((f-c)*(f-a)*(f-b)*(f-d)*(f-e)==0) continue;
                          for(g='0';g<='9';g++)
                          {
                               if((g-c)*(g-a)*(g-b)*(g-d)*(g-e)*(g-f)==0) continue;
                              for(h='0';h<='9';h++)
                              {
                                   if((h-c)*(h-a)*(h-b)*(h-d)*(h-e)*(h-f)*(h-g)==0) continue;
                                  for(i='0';i<='9';i++)
                                  {
                                       if((i-c)*(i-a)*(i-b)*(i-d)*(i-e)*(i-f)*(i-g)*(i-h)==0) continue;
                                      for(j='0';j<='9';j++)
                                      {
                                          if((j-c)*(j-a)*(j-b)*(j-d)*(j-e)*(j-f)*(j-g)*(j-h)*(j-i)==0) continue;
                                          m=(a-'0')*10000+(b-'0')*1000+(c-'0')*100+(d-'0')*10+(e-'0');
                                          n=(f-'0')*10000+(g-'0')*1000+(h-'0')*100+(i-'0')*10+(j-'0');
                                          if(m/n==x&&m%n==0) printf("%c%c%c%c%c/%c%c%c%c%c=%d\n",a,b,c,d,e,f,g,h,i,j,x);
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
      }
   }
return 0;
}
