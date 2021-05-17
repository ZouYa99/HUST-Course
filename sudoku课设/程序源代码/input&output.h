//
//  input&output.c
//  BinarySudoku
//
//  Created by ZouYa on 2021/2/20.
//
#include "header.h"

char* readFile(char* filename){
    FILE* fpr;
    int num=0,i;
    unsigned long length;
    char content[500000];
    fpr=fopen(filename, "r");
    if (fpr==NULL) {
        printf("opening file error while reading files!\n");
        exit(0);
    }
    //文件太长容易越界
    while (fread(&content[num], sizeof(char), 1, fpr)) {
        num++;
    }
    num=2;
    while(1)
    {
        if((content[num]==' ')&&(content[num-1]=='f')&&(content[num-2]=='n'))
        break;
        num++;
    }
    num=num+1;
    length=strlen(content);
    for (i=0; i<length; i++) {
        content[i]=content[i+num];
    }
    fclose(fpr);
    return content;
}

int transferNumber(char** content){
    int count=0,result=0,i,n,internal=1,mark=0;
    int before[10];
    if((**content==' ')||(**content=='\n')){
        *content=*content+1;
    }
    while((**content!=' ')&&(**content!='\n'))
    {
        if(((**content>'9')||(**content<'0'))&&(**content!='-')){
            return 0;
        }
        if(**content=='0'){
            before[count]=0;
        }
        if(**content=='-'){
            mark=1;
            count=count-1;
        }else{
            before[count]=(**content)-('1'-1);
        }
        count++;
        *content=*content+1;
    }
    for(i=0;i<count;i++)
    {
        for(n=0;n<i;n++)
        {
            internal=internal*10;
        }
        result=result+(internal*before[count-i-1]);
        internal=1;
    }
    if(mark==1){
        result=0-result;
    }
    return result;
}

CNF* createCNF(char* origin){
    char** contentPtr;
    CNF* current;
    Clause* sentence;
    Clause* lastSentence;
    Word* element;
    int i,var;
    current = (CNF*)malloc(sizeof(CNF));
    current->answer=NULL;
    current->begin=NULL;

    contentPtr=(char**)malloc(sizeof(char*));
    *contentPtr=origin;
    current->variableNumber=transferNumber(contentPtr)*2;
    current->clauseNumber=transferNumber(contentPtr);
    current->currentNumber=current->clauseNumber;

    for (i=0; i<current->clauseNumber; i++) {
        sentence = (Clause*)malloc(sizeof(Clause));
        sentence->next=NULL;
        sentence->length=0;
        sentence->status=1;
        sentence->begin=NULL;
        if (current->begin==NULL) {
            current->begin=sentence;
        }else{
            lastSentence->next=sentence;
        }
        element = (Word*)malloc(sizeof(Word));
        element->next=NULL;
        sentence->begin=element;
        while (1) {
            var=transferNumber(contentPtr);
            if(var==0){
                element->value=0;
                element->next=NULL;
                break;
            }else{
                element->value=var;
                element->next=(Word*)malloc(sizeof(Word));
                sentence->length++;
                element->status=1;
            }
            element=element->next;
            //printf("%d  ",var);
        }
        //printf("\n");
        lastSentence=sentence;
    }
    for (sentence=current->begin; sentence!=NULL; sentence=sentence->next) {
        element=sentence->begin;
        if (element->value==0) {
            lastSentence->next=sentence->next;
            continue;
        }
        while (element->next->value!=0) {
            element=element->next;
        }
        free(element->next);
        element->next=NULL;
        lastSentence=sentence;
    }
    return current;
}
