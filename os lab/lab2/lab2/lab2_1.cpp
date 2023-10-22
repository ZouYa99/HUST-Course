//
//  main.cpp
//  lab2_1
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

//union semun {
//    int              val;    /* Value for SETVAL */
//    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
//    unsigned short  *array;  /* Array for GETALL, SETALL */
//    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
//};


int num=100,semid;
struct sembuf sem;

void P(int semid,int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;    //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);    //1:表示执行命令的个数
    return;
}

void V(int semid,int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op =  1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}

void *subpf1(void*){
    int x1 = 0;
    while(true){
        P(semid,0);
        if (num<=0) {
            V(semid,0);
            break;
        }
        num--;
        cout<<"subp1 sell 1,remain:"<<num<<endl;
        x1++;
        V(semid,0);
    }
    cout<<"pthread 1 total number:"<<x1<<endl;
}

void *subpf2(void*){
    int x2=0;
    while(true){
        P(semid,0);
        if (num<=0) {
            V(semid,0);
            break;
        }
        num--;
        cout<<"subp2 sell 1,remain:"<<num<<endl;
        x2++;
        V(semid,0);
    }
    cout<<"pthread 2 total number:"<<x2<<endl;
}

void *subpf3(void*){
    int x3 = 0;
    while(true){
        P(semid,0);
        if (num<=0) {
            V(semid,0);
            break;
        }
        num--;
        cout<<"subp3 sell 1,remaining:"<<num<<endl;
        x3++;
        V(semid,0);
    }
    cout<<"pthread 3 total number:"<<x3<<endl;
}

int main(){
    pthread_t subp1,subp2,subp3;
    union semun arg;
    //创建一个信号灯
    semid = semget(IPC_PRIVATE,1,IPC_CREAT|0666);
    if(semid==-1){
        cout<<"semget error!";
        return 1;
    }
    //设置信号灯的量为1
    arg.val = 1;
    if(semctl(semid,0,SETVAL,arg)<0){
        cout<<"semctl error!";
        return 1;
    }
    //线程创建
    pthread_create(&subp1,NULL,subpf1,NULL);
    pthread_create(&subp2,NULL,subpf2,NULL);
    pthread_create(&subp3,NULL,subpf3,NULL);
    //线程等待
    pthread_join(subp1,NULL);
    pthread_join(subp2,NULL);
    pthread_join(subp3,NULL);
    //将信号灯集semid从内存中删除
    semctl(semid,0,IPC_RMID,arg);
    return 0;

}
