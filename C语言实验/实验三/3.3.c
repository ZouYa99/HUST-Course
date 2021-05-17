#include <stdio.h>
#include <stdlib.h>
enum {copy,start};
int main()
{
    char c;
    int state=copy;
    c=getchar();
    judge:
        for(;c!='\n';c=getchar()){
            switch(state){
            case copy:
                if(c==' ') {state=start;putchar(' ');}
                else putchar(c);break;
            case start:
                if(c!=' ') {state=copy;putchar(c);}
                else ;
            }
        }
    if(c=='\n'){
        c=getchar();
        for(;c=='\n';)c=getchar();
        if(c!='\n') goto judge;
    }
    return 0;
}
