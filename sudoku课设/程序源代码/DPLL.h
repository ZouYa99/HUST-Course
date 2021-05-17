//
//  DPLL.c
//  BinarySudoku
//
//  Created by ZouYa on 2021/2/20.
//

#include "header.h"

//单子句出现时，如果出现该变元的字句直接去掉，如果出现该变元的否定则把该文字去掉
//按照策略选词
//选词取真值or取假值


int chooseVariable(CNF* current){

    int shortest=59999;
    int flag=0,i,choice=1;
    int longest=0;
    Clause* cur;
    Clause* specific;
    Word* curWord;
    cur = current->begin;
    specific = cur;
    while (cur!=NULL) {
        if ((cur->status==1)&&(cur->length<shortest)) {
            shortest = cur->length;
            specific = cur;
        }
        if ((cur->status==1)&&(cur->length>longest)) {
            longest = cur->length;
        }
        cur = cur->next;
    }// 找到最小长度以及长度最小的子句
//    //优化前的变元选择方案
//    while (curWord!=NULL) {
//        if (curWord->status==1) {
//            choice = curWord->value;
//            break;
//        }
//        curWord = curWord->next;
//    }
//    return choice;
    
    int averageLength = (shortest+longest)/2;
    int len = current->variableNumber;
    Variable count[len];
    for(i=0;i<len;i++){
        count[i].amount=0;
        count[i].value=0;
        count[i].status=0;
    }
    cur = current->begin;
    while (cur!=NULL) {
        if ((cur->length<=averageLength)&&(cur->status==1)) {
            flag=1;
            curWord=cur->begin;
            while (curWord!=NULL) {
                if (curWord->status==1) {
                    for (i=0; i<len; i++) {
                        if(count[i].status==1){
                            if(count[i].value==curWord->value){
                                count[i].amount++;
                            }
                        }else{
                            count[i].amount++;
                            count[i].status=1;
                            count[i].value=curWord->value;
                            break;
                        }
                    }
                }
                curWord=curWord->next;
            }
        }
        cur=cur->next;
    }
//    for (i=0; i<len; i++) {
//        printf("%d ",count[i].value);
//    }
    if (flag==1) {
        int largest=0;
        for (i=0; i<len; i++) {
            if (count[i].amount>count[largest].amount) {
                largest=i;
            }
        }
        return count[largest].value;
    }else{
        curWord = specific->begin;
        while (curWord!=NULL) {
            if (curWord->status==1) {
                choice = curWord->value;
                break;
            }
            curWord = curWord->next;
        }
        return choice;
    }
    
    
}


int simplify(CNF* current,int tag){
    Clause* cur=current->begin;
    Word* curWord;
    for (; cur!=NULL; cur=cur->next) {
        curWord=cur->begin;
        for (; curWord!=NULL; curWord=curWord->next) {
            if (curWord->value==tag) {
                cur->status--;
                if (cur->status==0) {
                    current->currentNumber--;
                }
            }
            if (curWord->value==(0-tag)) {
                curWord->status=0;
                cur->length--;
            }
        }
    }
    if (current->currentNumber==0) {
        return 1;
    }else{
        return 0;
    }
}

int backward(CNF* current,int tag){
    Clause* cur=current->begin;
    Word* curWord;
    for (; cur!=NULL; cur=cur->next) {
        curWord=cur->begin;
        for (; curWord!=NULL; curWord=curWord->next) {
            if (curWord->value==tag) {
                cur->status++;
                if (cur->status==1) {
                    current->currentNumber++;
                }
            }
            if (curWord->value==(0-tag)) {
                curWord->status=1;
                cur->length++;
            }
        }
    }
    if (current->currentNumber==0) {
        return 1;
    }else{
        return 0;
    }
}

int DPLL(CNF* current,Word* curAns){
    int tag=1,status=0,flag=0;
    Clause* cur=current->begin;
    Word* curWord;
    Word* answer;
    answer = curAns;
    if (current->currentNumber==0) {
        return 1;
    }
    while (cur!=NULL) {
        if ((cur->length==0)&&(cur->status==1)) {
            return 0;
        }
        cur=cur->next;
    }
    for (cur=current->begin; cur!=NULL; cur=cur->next) {
        if ((cur->length==1)&&(cur->status==1)) {
            curWord=cur->begin;
            while (curWord!=NULL) {
                if (curWord->status==1) {
                    tag=curWord->value;
                    flag=1;
                    break;
                }
                curWord=curWord->next;
            }
            break;
        }
    }
    if (flag==1) {
        if (simplify(current, tag)) {
            answer = curAns;
            while(answer->next!=NULL)
                answer=answer->next;
            answer->value=tag;
            answer->next=(Word*)malloc(sizeof(Word));
            answer->next->next=NULL;
            return 1;
        }else{
            status = DPLL(current,curAns);
            if (status) {
                answer = curAns;
                while(answer->next!=NULL)
                    answer=answer->next;
                answer->value=tag;
                answer->next=(Word*)malloc(sizeof(Word));
                answer->next->next=NULL;
                return 1;
            }else{
                backward(current, tag);
                return 0;
            }
        }
    }
    
    if (current->currentNumber==0) {
        return 1;
    }
    cur=current->begin;
    while (cur!=NULL) {
        if ((cur->length==0)&&(cur->status==1)) {
            return 0;
        }
        cur=cur->next;
    }
    
    tag=chooseVariable(current);
    simplify(current, tag);
    if (DPLL(current, curAns)) {
        answer = curAns;
        while(answer->next!=NULL)
            answer=answer->next;
        answer->value=tag;
        answer->next=(Word*)malloc(sizeof(Word));
        answer->next->next=NULL;
        return 1;
    }else{
        backward(current, tag);
        tag=(0-tag);
        simplify(current, tag);
        if (DPLL(current, curAns)) {
            answer = curAns;
            while(answer->next!=NULL)
                answer=answer->next;
            answer->value=tag;
            answer->next=(Word*)malloc(sizeof(Word));
            answer->next->next=NULL;
            return 1;
        }else{
            backward(current, tag);
            return 0;
        }
    }
}

int DPLLMain(char* filename,int isSudoku){
    time_t start,end;
    long duration;
    FILE* fp;
    CNF* current;
    Word *answer,*curAns;
    int DPLLStatus,i;
    long nameLength;
    nameLength=strlen(filename);
    char name[nameLength+1];
    
    char *sudokuName="/Users/mac/Desktop/BinarySudoku/BinarySudoku/BinarySudoku.cnf\0";
    
    answer=(Word*)malloc(sizeof(Word));
    answer->next=NULL;
    answer->value=0;
    
    if (strlen(filename)==0) {
        printf("请重新输入文件名\n");
        scanf("%s",filename);
    }
    if (isSudoku==0) {
        current=createCNF(readFile(filename));
    }else{
        current=createCNF(readFile(sudokuName));
    }
    
    time(&start);
    DPLLStatus=DPLL(current, answer);
    time(&end);
    duration=end-start;
    
    if (isSudoku==0) {
        for (i=0; i<nameLength; i++) {
            name[i]=*(filename+i);
        }
        name[nameLength-3]='r';
        name[nameLength-2]='e';
        name[nameLength-1]='s';
        name[nameLength]='\0';
        printf("%s\n",name);
        fp=fopen(name, "w");
        if (fp==NULL) {
            printf("open file error when writing!\n");
            return 0;
        }
        fputs("s ",fp);
        fprintf(fp,"%d\n",DPLLStatus);
        fputs("v ",fp);
        curAns=answer;
        //按照顺序输出
        int mark[(current->variableNumber)/2];
        Word* answerCur = curAns;
        while(answerCur->next!=NULL)
        {
            if (answerCur->value>0) {
                mark[answerCur->value-1]=1;
            }
            if (answerCur->value<0) {
                mark[-(answerCur->value)-1]=0;
            }
            answerCur=answerCur->next;
        }
        for (i=0; i<(current->variableNumber)/2; i++) {
            if (mark[i]==1) {
                fprintf(fp,"%d ",i+1);
            }
            if (mark[i]==0) {
                fprintf(fp,"%d ",-(i+1));
            }
        }
        
        fputs("\n",fp);
        fputs("t ",fp);
        fprintf(fp,"%ld",duration*1000);
        fclose(fp);
    }else if(isSudoku==1){
        if (DPLLStatus) {
            int op;
            printf("wanna play(1) or show the answer(2)\n");
            scanf("%d",&op);
            if (op==1) {
                displaySudoku(answer, filename,1);
            }
            if (op==2) {
                displaySudoku(answer, filename,2);
            }
        }else{
            printf("数独无解");
            return 0;
        }
    }
    
    
    Clause* curClause,*lastClause;
    Word* curWord;
    curClause=current->begin;
    while (curClause!=NULL) {
        curWord=curClause->begin;
        while (curWord!=NULL) {
            free(curWord);
            curWord=curWord->next;
        }
        lastClause=curClause;
        curClause=curClause->next;
        free(lastClause);
    }
    free(current);
    return 0;
}

