//
//  header.h
//  lab3
//
//  Created by ZouYa on 2021/12/23.
//

#ifndef header_h
#define header_h

#include<sys/types.h>
#include<iostream>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

#define STATUS_PENDING  0x01
#define STATUS_READ     0x02
#define STATUS_WRITTEN  0x04
#define STATUS_ALL      0x08
#define STATUS_HEAD     0x10
#define STATUS_TAIL     0x20
#define SIZE_HEADER 5

using namespace::std;
#define buffer_size 128  //缓冲区大小
#define buffer_num 64
//union semun {
//    int val; /* value for SETVAL */
//    struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
//    unsigned short *array; /* array for GETALL, SETALL */
//    struct seminfo *__buf; /* buffer for IPC_INFO */
//};

void P(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;    //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);    //1:表示执行命令的个数
    return;
}

void V(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op =  1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}

typedef struct Buffer{
    char data[buffer_size];  //数据区
    unsigned long size;
    int  nextshm;
    unsigned char status;
}Buffer;

#endif /* header_h */
