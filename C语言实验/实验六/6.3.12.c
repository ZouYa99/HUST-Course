//
//  main.c
//  6.3.12
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
void task0(void){
    printf("Task0 is called!\n");
}
void task1(void){
    printf("Task1 is called!\n");
}
void task2(void){
    printf("Task2 is called!\n");
}
void task3(void){
    printf("Task3 is called!\n");
}
void task4(void){
    printf("Task4 is called!\n");
}
void task5(void){
    printf("Task5 is called!\n");
}
void task6(void){
    printf("Task6 is called!\n");
}
void task7(void){
    printf("Task7 is called!\n");
}
void scheduler(void);
void execute(void (*func[])(void),int number);
int main(void) {
    scheduler();
    return 0;
}
void scheduler(void){
    int num[8];
    int i=0,number;
    while (i<8&&isdigit(num[i]=getchar())) {
        num[i++]-='0';
    }
    number=i;
    void (*func[number])(void);
    for (i=0; i<number; i++) {
        switch (num[i]) {
            case 0:
            func[i]=task0;break;
            case 1:
            func[i]=task1;break;
            case 2:
            func[i]=task2;break;
            case 3:
            func[i]=task3;break;
            case 4:
            func[i]=task4;break;
            case 5:
            func[i]=task5;break;
            case 6:
            func[i]=task6;break;
            case 7:
            func[i]=task7;break;
        }
    }
    execute(func, number);
}
void execute(void (*func[])(void),int number){
    int j;
    for (j=0; j<number; j++) {
        func[j]();
    }
}
