//
//  main.c
//  BinarySudoku
//
//  Created by ZouYa on 2021/2/20.
//


//#include "input&output.c"
#include "header.h"
#include "DPLL.h"
#include "input&output.h"

int main() {
    // insert code here...
    int choice=1;
    char filename[100];
    while (1) {
        printf("--------Welcome!!--------\n");
        printf("---Make your choice!!----\n");
        printf("------1.solve DPLL-------\n");
        printf("------2.binary sudoku----\n");
        printf("------3.exit-------------\n");
        printf("-------------------------\n");
        scanf("%d",&choice);
        if (choice==1) {
            printf("Input the file name of SAT problem\n");
            scanf("%s",filename);
            DPLLMain(filename, 0);
        }
        if (choice==2) {
            printf("Input the file name of binary sudoku\n");
            scanf("%s",filename);
            sudokuMain(filename);
            DPLLMain(filename, 1);
        }
        if (choice==3) {
            return 0;
        }
    }
    
    return 0;
}
