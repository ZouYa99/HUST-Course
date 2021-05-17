//
//  header.h
//  BinarySudoku
//
//  Created by ZouYa on 2021/2/20.
//

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

//status默认输入时为1，设置为0时表示删去
#ifndef something
#define something


typedef struct Word{
    int value;
    int status;
    struct Word *next;
} Word;

typedef struct Clause{
    int length;
    int status;
    Word* begin;
    struct Clause* next;
}Clause;

typedef struct CNF{
    int variableNumber;
    int clauseNumber;
    int currentNumber;
    Clause* begin;
    Word* answer;
}CNF;

//用于统计变元的时候
typedef struct Variable{
    int value;
    int amount;
    int status;
} Variable;

//用于数独转换的子句创建
typedef struct Element{
    int value;
    struct Element *next;
} Element;

typedef struct Sentence{
    Element* begin;
    struct Sentence* next;
} Sentence;

char* readFile(char* filename);
int transferNumber(char** content);
CNF* createCNF(char* origin);

int chooseVariable(CNF* current);
int simplify(CNF* current,int tag);
int backward(CNF* current,int tag);
int DPLL(CNF* current,Word* curAns);

int createVariableClause(Sentence* start,int status,int row,int column);
int createCNFFileForSudoku(Sentence* start,int sentenceNumber,int elementNumber);
int limitedcontinuity(Sentence* start,int type);
int limitedSameNumber(Sentence* start);
int addLimitInRow(Sentence* start,int a,int b,int c,int d,int row);
int addLimitInColumn(Sentence* start,int a,int b,int c,int d,int column);
int addElement(Element* start,int value);
int addNotSameRowOrColumn(Sentence* start);

int sudokuMain(char* filename);
int displaySudoku(Word* answerStart,char *filename,int choice);

#endif
