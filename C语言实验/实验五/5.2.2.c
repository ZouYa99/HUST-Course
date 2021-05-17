//
//  main.c
//  5.2.2
//
//  Created by 雅 on 2019/11/18.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include<string.h>
void RemoveDuplicate(char *s);
int ascii[256];
int main()
{
    char str[200];
    printf("Input strings,end of Ctrl+z\n");
    while(fgets(str,200,stdin)!=NULL)
    {

        RemoveDuplicate(str);
        printf("%s",str);

    }
    return 0;
}

void RemoveDuplicate(char *s)
{
    int r,w,len;
    len=strlen(s);
    for(r=w=0;r<len;r++)
    {
        if(ascii[(int)s[r]]!=1)
        {
          s[w++]=s[r];
            ascii[(int)s[r]]=1;
        }
    }
    s[w]='\0';
}
