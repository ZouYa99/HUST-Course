//
//  sudoku.c
//  BinarySudoku
//
//  Created by ZouYa on 2021/2/20.
//

#include "header.h"

int createVariableClause(Sentence* start,int status,int row,int column){
    
    int value = ((row+1)*10 + column + 1);
    Sentence* cur=start;
    while (cur->next!=NULL) {
        cur=cur->next;
    }
    if (status==1) {
        cur->next = (Sentence*)malloc(sizeof(Sentence));
        cur->next->next = NULL;
        cur->next->begin = NULL;
        cur->begin = (Element*)malloc(sizeof(Element));
        cur->begin->value = value;
        cur->begin->next = NULL;
    }

    if (status==0) {
        cur->next = (Sentence*)malloc(sizeof(Sentence));
        cur->next->next = NULL;
        cur->next->begin = NULL;
        cur->begin = (Element*)malloc(sizeof(Element));
        cur->begin->value = 0 - value;
        cur->begin->next = NULL;
    }
    
    return 1;
}

int createCNFFileForSudoku(Sentence* start,int sentenceNumber,int elementNumber){
    FILE* fp;
    const char* filename = "/Users/mac/Desktop/BinarySudoku/BinarySudoku/BinarySudoku.cnf\0";
    Sentence* current = start;
    Element* curElement;
    fp=fopen(filename, "w");
    if (fp == NULL){
        printf("file open error while creating file for sudoku!\n");
        return -1;
    }
    fputs("p cnf ", fp);
    fprintf(fp, "%d ",elementNumber);
    fprintf(fp, "%d\n",sentenceNumber);
    while (current->next!=NULL) {
        curElement = current->begin;
        while (curElement!=NULL) {
            fprintf(fp, "%d ",curElement->value);
            curElement=curElement->next;
        }
        fputs("0\n", fp);
        current=current->next;
    }
    fclose(fp);
    return 1;
}

int limitedcontinuity(Sentence* start,int type){
    int row,column;
    Sentence* current;
    Element *present;
    current=start;
    
    while (current->next!=NULL) {
        current=current->next;
    }
    
    //行连续 1
    for (row=1; row<=type; row++) {
        for (column=3; column<=type; column++) {
            column=column-2;
            present=(Element*)malloc(sizeof(Element));
            present->value=(row*10)+column;
            present->next=NULL;
            current->begin=present;
            column++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=(row*10)+column;
            present->next->next=NULL;
            present=present->next;
            column++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=(row*10)+column;
            present->next->next=NULL;
            
            current->next=(Sentence*)malloc(sizeof(Sentence));
            current=current->next;
            current->next=NULL;
            current->begin=NULL;
        }
    }
    //行连续 0
    for (row=1; row<=type; row++) {
        for (column=3; column<=type; column++) {
            column=column-2;
            present=(Element*)malloc(sizeof(Element));
            present->value=0-((row*10)+column);
            present->next=NULL;
            current->begin=present;
            column++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=0-((row*10)+column);
            present->next->next=NULL;
            present=present->next;
            column++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=0-((row*10)+column);
            present->next->next=NULL;
            
            current->next=(Sentence*)malloc(sizeof(Sentence));
            current=current->next;
            current->next=NULL;
            current->begin=NULL;
        }
    }
    //列连续 1
    for (column=1; column<=type; column++) {
        for (row=3; row<=type; row++) {
            row=row-2;
            present=(Element*)malloc(sizeof(Element));
            present->value=(row*10)+column;
            present->next=NULL;
            current->begin=present;
            row++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=(row*10)+column;
            present->next->next=NULL;
            present=present->next;
            row++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=(row*10)+column;
            present->next->next=NULL;
            
            current->next=(Sentence*)malloc(sizeof(Sentence));
            current=current->next;
            current->next=NULL;
            current->begin=NULL;
        }
    }
    //列连续 0
    for (column=1; column<=type; column++) {
        for (row=3; row<=type; row++) {
            row=row-2;
            present=(Element*)malloc(sizeof(Element));
            present->value=0-((row*10)+column);
            present->next=NULL;
            current->begin=present;
            row++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=0-((row*10)+column);
            present->next->next=NULL;
            present=present->next;
            row++;
            present->next=(Element*)malloc(sizeof(Element));
            present->next->value=0-((row*10)+column);
            present->next->next=NULL;
            
            current->next=(Sentence*)malloc(sizeof(Sentence));
            current=current->next;
            current->next=NULL;
            current->begin=NULL;
        }
    }
    
    return 1;
}

int limitedSameNumber(Sentence* start){
    Sentence* current;
    current=start;
    int row,column;
    for (row=1; row<=6; row++) {
        addLimitInRow(current, 1, 2, 3, 4, row);
        addLimitInRow(current, 1, 2, 3, 5, row);
        addLimitInRow(current, 1, 2, 3, 6, row);
        addLimitInRow(current, 1, 2, 4, 5, row);
        addLimitInRow(current, 1, 2, 4, 6, row);
        addLimitInRow(current, 1, 2, 5, 6, row);
        addLimitInRow(current, 2, 3, 4, 5, row);
        addLimitInRow(current, 2, 3, 4, 6, row);
        addLimitInRow(current, 2, 3, 5, 6, row);
        addLimitInRow(current, 3, 4, 5, 6, row);
        addLimitInRow(current, 1, 3, 4, 5, row);
        addLimitInRow(current, 1, 3, 4, 6, row);
        addLimitInRow(current, 1, 3, 5, 6, row);
        addLimitInRow(current, 1, 4, 5, 6, row);
        addLimitInRow(current, 2, 4, 5, 6, row);
    }
    for (row=1; row<=6; row++) {
        addLimitInRow(current, -1, -2, -3, -4, 0-row);
        addLimitInRow(current, -1, -2, -3, -5, 0-row);
        addLimitInRow(current, -1, -2, -3, -6, 0-row);
        addLimitInRow(current, -1, -2, -4, -5, 0-row);
        addLimitInRow(current, -1, -2, -4, -6, 0-row);
        addLimitInRow(current, -1, -2, -5, -6, 0-row);
        addLimitInRow(current, -2, -3, -4, -5, 0-row);
        addLimitInRow(current, -2, -3, -4, -6, 0-row);
        addLimitInRow(current, -2, -3, -5, -6, 0-row);
        addLimitInRow(current, -3, -4, -5, -6, 0-row);
        addLimitInRow(current, -1, -3, -4, -5, 0-row);
        addLimitInRow(current, -1, -3, -4, -6, 0-row);
        addLimitInRow(current, -1, -3, -5, -6, 0-row);
        addLimitInRow(current, -1, -4, -5, -6, 0-row);
        addLimitInRow(current, -2, -4, -5, -6, 0-row);
    }
    for (column=1; column<=6; column++) {
        addLimitInColumn(current, 1, 2, 3, 4, column);
        addLimitInColumn(current, 1, 2, 3, 5, column);
        addLimitInColumn(current, 1, 2, 3, 6, column);
        addLimitInColumn(current, 1, 2, 4, 5, column);
        addLimitInColumn(current, 1, 2, 4, 6, column);
        addLimitInColumn(current, 1, 2, 5, 6, column);
        addLimitInColumn(current, 1, 3, 4, 5, column);
        addLimitInColumn(current, 1, 3, 4, 6, column);
        addLimitInColumn(current, 1, 3, 5, 6, column);
        addLimitInColumn(current, 1, 4, 5, 6, column);
        addLimitInColumn(current, 2, 3, 4, 5, column);
        addLimitInColumn(current, 2, 3, 4, 6, column);
        addLimitInColumn(current, 2, 3, 5, 6, column);
        addLimitInColumn(current, 2, 4, 5, 6, column);
        addLimitInColumn(current, 3, 4, 5, 6, column);
    }
    for (column=1; column<=6; column++) {
        addLimitInColumn(current, -1, -2, -3, -4, 0-column);
        addLimitInColumn(current, -1, -2, -3, -5, 0-column);
        addLimitInColumn(current, -1, -2, -3, -6, 0-column);
        addLimitInColumn(current, -1, -2, -4, -5, 0-column);
        addLimitInColumn(current, -1, -2, -4, -6, 0-column);
        addLimitInColumn(current, -1, -2, -5, -6, 0-column);
        addLimitInColumn(current, -1, -3, -4, -5, 0-column);
        addLimitInColumn(current, -1, -3, -4, -6, 0-column);
        addLimitInColumn(current, -1, -3, -5, -6, 0-column);
        addLimitInColumn(current, -1, -4, -5, -6, 0-column);
        addLimitInColumn(current, -2, -3, -4, -5, 0-column);
        addLimitInColumn(current, -2, -3, -4, -6, 0-column);
        addLimitInColumn(current, -2, -3, -5, -6, 0-column);
        addLimitInColumn(current, -2, -4, -5, -6, 0-column);
        addLimitInColumn(current, -3, -4, -5, -6, 0-column);
    }
    return 1;
}

int addLimitInRow(Sentence* start,int a,int b,int c,int d,int row){
    Sentence* current;
    Element* curElement;
    current=start;
    while (current->next!=NULL) {
        current=current->next;
    }
    current->next=(Sentence*)malloc(sizeof(Sentence));
    current=current->next;
    current->next=NULL;
    curElement=(Element*)malloc(sizeof(Element));
    curElement->value=row*10+a;
    current->begin=curElement;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=row*10+b;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=row*10+c;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=row*10+d;
    curElement->next=NULL;
    
    return 1;
}

int addLimitInColumn(Sentence* start,int a,int b,int c,int d,int column){
    Sentence* current;
    Element* curElement;
    current=start;
    while (current->next!=NULL) {
        current=current->next;
    }
    current->next=(Sentence*)malloc(sizeof(Sentence));
    current=current->next;
    current->next=NULL;
    curElement=(Element*)malloc(sizeof(Element));
    curElement->value=a*10+column;
    current->begin=curElement;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=b*10+column;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=c*10+column;
    curElement->next=(Element*)malloc(sizeof(Element));
    curElement=curElement->next;
    curElement->value=d*10+column;
    curElement->next=NULL;
    
    return 1;
}

int addElement(Element* start,int value){
    Element* current;
    current=start;
    while (current->next!=NULL) {
        current=current->next;
    }
    current->value=value;
    current->next=(Element*)malloc(sizeof(Element));
    current->next->next=NULL;
    
    return 1;
}

int addNotSameRowOrColumn(Sentence* start){
    int i, n,a;
    Sentence* clausepointer;
    Element* itemPointer;
    clausepointer = start;
    while (clausepointer->next != NULL)
        clausepointer = clausepointer->next;
    clausepointer->begin = (Element*)malloc(sizeof(Element));
    clausepointer->begin->next = NULL;
    for (i = 1; i < 7; i++)
    {
        for (n = i + 1; n < 7; n++)
        {
            //最后为1
            for (a = 1; a < 7; a++)
            {    //1 i n a 1
                itemPointer = clausepointer->begin;
            addElement(itemPointer, (i * 10 + a));
            addElement(itemPointer, (0 - (10000 + i * 1000 + n * 100 + a * 10 + 1)));
            itemPointer->next->next = NULL;
            clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
            clausepointer = clausepointer->next;
            clausepointer->begin = (Element*)malloc(sizeof(Element));
            clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 1
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (n * 10 + a));
                addElement(itemPointer, (0 - (10000 + i * 1000 + n * 100 + a * 10 + 1)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 1
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0-(i * 10 + a));
                addElement(itemPointer, 0-(n * 10 + a));
                addElement(itemPointer, (10000 + i * 1000 + n * 100 + a * 10 + 1));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }

            //最后为0
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0-(i * 10 + a));
                addElement(itemPointer, (0 - (10000 + i * 1000 + n * 100 + a * 10 )));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0-(n * 10 + a));
                addElement(itemPointer, (0 - (10000 + i * 1000 + n * 100 + a * 10)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (i * 10 + a));
                addElement(itemPointer, (n * 10 + a));
                addElement(itemPointer, (10000 + i * 1000 + n * 100 + a * 10 ));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            
            
            //四位数的约束
            for (a = 1; a < 7; a++)
            {    //1 i n a
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0-(10000+i*1000+n*100+a*10+1));
                addElement(itemPointer, (1000+i*100+n*10+a));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (10000 + i * 1000 + n * 100 + a * 10));
                addElement(itemPointer, (1000 + i * 100 + n * 10 + a));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (10000 + i * 1000 + n * 100 + a * 10 + 1));
                addElement(itemPointer, (10000 + i * 1000 + n * 100 + a * 10));
                addElement(itemPointer, 0-(1000 + i * 100 + n * 10 + a));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            
            //三位数的第一个子句
            itemPointer = clausepointer->begin;
            addElement(itemPointer, 0 - (100 + i * 10 + n));
            for(a=1;a<7;a++)
            {
                addElement(itemPointer, 0 - (1000 + i * 100 + n * 10 + a));
            }
            
            //三位数的后面几个子句
            while (itemPointer->next->next != NULL)
                itemPointer = itemPointer->next;
            itemPointer->next = NULL;
            clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
            clausepointer = clausepointer->next;
            clausepointer->begin = (Element*)malloc(sizeof(Element));
            clausepointer->begin->next = NULL;
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (1000 + i * 100 + n * 10 + a));
                addElement(itemPointer, (100 + i * 10 + n));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
                
            }


            //重复一遍列
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (a * 10 + i));
                addElement(itemPointer, (0 - (20000 + i * 1000 + n * 100 + a * 10 + 1)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (a * 10 + n));
                addElement(itemPointer, (0 - (20000 + i * 1000 + n * 100 + a * 10 + 1)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (a * 10 + i));
                addElement(itemPointer, 0 - (a * 10 + n));
                addElement(itemPointer, (20000 + i * 1000 + n * 100 + a * 10 + 1));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }


            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (a * 10 + i));
                addElement(itemPointer, (0 - (20000 + i * 1000 + n * 100 + a * 10)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (a * 10 + n));
                addElement(itemPointer, (0 - (20000 + i * 1000 + n * 100 + a * 10)));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {    //1 i n a 0
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (a * 10 + i));
                addElement(itemPointer, (a * 10 + n));
                addElement(itemPointer, (20000 + i * 1000 + n * 100 + a * 10));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (20000 + i * 1000 + n * 100 + a * 10 + 1));
                addElement(itemPointer, (2000 + i * 100 + n * 10 + a));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, 0 - (20000 + i * 1000 + n * 100 + a * 10));
                addElement(itemPointer, (2000 + i * 100 + n * 10 + a));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (20000 + i * 1000 + n * 100 + a * 10 + 1));
                addElement(itemPointer, (20000 + i * 1000 + n * 100 + a * 10));
                addElement(itemPointer, 0 - (2000 + i * 100 + n * 10 + a));
                itemPointer->next->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
            }
            itemPointer = clausepointer->begin;
            addElement(itemPointer, 0 - (200 + i * 10 + n));
            for (a = 1; a < 7; a++)
            {
                addElement(itemPointer, 0 - (2000 + i * 100 + n * 10 + a));
            }
            while (itemPointer->next->next != NULL)
                itemPointer = itemPointer->next;
            itemPointer->next = NULL;
            clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
            clausepointer = clausepointer->next;
            clausepointer->begin = (Element*)malloc(sizeof(Element));
            clausepointer->begin->next = NULL;
            for (a = 1; a < 7; a++)
            {
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (2000 + i * 100 + n * 10 + a));
                addElement(itemPointer, (200 + i * 10 + n));
                itemPointer->next->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;

            }
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (200 + i * 10 + n));
                itemPointer->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
                
                itemPointer = clausepointer->begin;
                addElement(itemPointer, (100 + i * 10 + n));
                itemPointer->next = NULL;
                clausepointer->next = (Sentence*)malloc(sizeof(Sentence));
                clausepointer = clausepointer->next;
                clausepointer->begin = (Element*)malloc(sizeof(Element));
                clausepointer->begin->next = NULL;
        }
    }
    clausepointer->next = NULL;
    clausepointer->begin = NULL;
    
    return 1;
}

int sudokuMain(char* filename){
    
    int input[6][6];
    int row=6,column=6;
    int i,j;
    int sentenceNumber=0,elementNumber;
    
    FILE* fp;
    fp=fopen(filename, "r");
    if (fp==NULL) {
        printf("open file error while reading sudoku!\n");
        return 0;
    }
    Sentence *start,*current;
    Sentence* lastSentence;
    Element *curElement;
    start=(Sentence*)malloc(sizeof(Sentence));
    start->begin=NULL;
    start->next=NULL;
    lastSentence=start;
    for (i = 0; i < row; i++){
        for (j = 0; j < column; j++){
            fscanf(fp,"%d",&input[i][j]);
        }
    }
    for (i = 0; i < row; i++){
        for (j = 0; j < column; j++){
            printf("%d ",input[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i=0; i<row; i++) {
        for (j=0; j<column; j++) {
            if (input[i][j]!=3) {
                createVariableClause(start, input[i][j], i, j);
            }
        }
    }
    limitedcontinuity(start, 6);
    limitedSameNumber(start);
    addNotSameRowOrColumn(start);
    current=start;
    while (current->next!=NULL) {
        curElement=current->begin;
        if (curElement==NULL) {
            lastSentence->next=current->next;
        }
        if (curElement!=NULL) {
            sentenceNumber++;
        }
        lastSentence=current;
        current=current->next;
    }
    elementNumber=606;
    createCNFFileForSudoku(start, sentenceNumber, elementNumber);
    return 1;
}
int displaySudoku(Word* answerStart,char *filename,int choice){
    
    int i,j,num,unknown=0,row,column;
    FILE* fp;
    int answerSheet[36];
    int matrix[6][6];
    int input[6][6];
    int isCorrect=1;
    int seeOrNot;
    Word* current;
    current=answerStart;
    i=0;
    while (current->next!=NULL) {
        if ((current->value>=-66)&&(current->value<=66)) {
            answerSheet[i]=current->value;
            i++;
        }
        current=current->next;
    }
    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            for(num=0;num<36;num++){
                if(answerSheet[num]==((i+1)*10+j+1)){
                    matrix[i][j]=1;
                    break;
                }
                if(answerSheet[num]==0-((i+1)*10+j+1))
                {
                    matrix[i][j]=0;
                    break;
                }
            }
        }
    }
    if (choice==2) {
        for (i=0; i<6; i++) {
            for (j=0; j<6; j++) {
                printf("%d ",matrix[i][j]);
            }
            printf("\n");
        }
        return 1;
    }
    
    if (choice==1) {
        fp=fopen(filename, "r");
        if (fp==NULL) {
            printf("open file error while reading sudoku file\n");
            return 1;
        }
        for (i=0; i<6; i++) {
            for (j=0; j<6; j++) {
                fscanf(fp,"%d",&input[i][j]);
                if (input[i][j]==3) {
                    unknown++;
                }
            }
        }
        
        printf("solve binary sudoku below:\n");
        for (i=0; i<6; i++) {
            for (j=0; j<6; j++) {
                printf("%d ",input[i][j]);
            }
            printf("\n");
        }
        
        for (int n=0; n<unknown; n++) {
            printf("请输入你想输入的位置的行和列\n");
            scanf("%d",&row);
            scanf("%d",&column);
            printf("请输入你想输入的数字\n");
            scanf("%d",&input[row-1][column-1]);
            
            for (i=0; i<6; i++) {
                for (j=0; j<6; j++) {
                    printf("%d ",input[i][j]);
                }
                printf("\n");
            }
        }
        
        for (i=0; i<6; i++) {
            for (j=0; j<6; j++) {
                if (input[i][j]!=matrix[i][j]) {
                    isCorrect=0;
                    break;
                }
            }
            if (isCorrect==0) {
                break;
            }
        }
        if (isCorrect==1) {
            printf("congratulations!\n");
        }
        if (isCorrect==0) {
            printf("sorry,do you want to see the answer?yes(1)no(0)\n");
            scanf("%d",&seeOrNot);
            if (seeOrNot==1) {
                for (i=0; i<6; i++) {
                    for (j=0; j<6; j++) {
                        printf("%d ",matrix[i][j]);
                    }
                    printf("\n");
                }
            }
        }

    }
        
    return 1;
}
