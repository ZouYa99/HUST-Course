//
//  lab2_2.cpp
//  lab2
//
//  Created by ZouYa on 2021/12/17.
//

#include<sys/types.h>
#include<iostream>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>

using namespace std;
#define TOTAL 100

union semun {
    int val; /* value for SETVAL */
    struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};
int a=0,semid; //共享缓冲区

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

void *cacu_f(void*){
    for(int i=0;i<100;i++){
        P(semid,0);
        a++;
        if(a%2==0){
            V(semid,1);
        }else{
            V(semid,2);
        }
    }
}
void *print1(void*){
    int x1=0;
    for (int i=0; i<50; i++) {
        P(semid,1);
        cout<<"pthread1 print even num: "<<a<<endl;
        x1++;
        V(semid,0);
    }
    cout<<"pthread1 print times: "<<x1<<" times"<<endl;
}

void *print2(void*){
    int x2=0;
    for (int i=0; i<50; i++) {
        P(semid,2);
        cout<<"pthread2 print odd num: "<<a<<endl;
        x2++;
        V(semid,0);
    }
    cout<<"pthread 2 print times: "<<x2<<" times"<<endl;
}

int main(){
    pthread_t caculate,p1,p2;
    union semun arg;
    semid = semget(IPC_PRIVATE,3,IPC_CREAT|0666);
    //0号：init=1 表计算进程的资源数
    //1号：init=0 偶数资源数
    //2号：init=0 奇数资源数
    if(semid==-1){
        cout<<"semget error!"<<endl;
        return -1;
    }
    arg.val = 1;
    if(semctl(semid,0,SETVAL,arg)<0){
        cout<<"semctl error"<<endl;
        return -1;
    }
    arg.val=0;
    if(semctl(semid,1,SETVAL,arg)<0){
        cout<<"semctl error"<<endl;
        return -1;
    }
    if(semctl(semid,2,SETVAL,arg)<0){
        cout<<"semctl error"<<endl;
        return -1;
    }
    
    pthread_create(&caculate,NULL,cacu_f,NULL);
    pthread_create(&p1,NULL,print1,NULL);
    pthread_create(&p2,NULL,print2,NULL);

    pthread_join(caculate,NULL);
    pthread_join(p1,NULL);
    pthread_join(p1,NULL);

    semctl(semid,3,IPC_RMID,arg);
    return 0;
}
