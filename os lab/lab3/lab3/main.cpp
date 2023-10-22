//
//  main.cpp
//  lab3
//
//  Created by ZouYa on 2021/12/23.
//

#include "header.h"

union semun arg;
struct sembuf sem;
char c;

int main(int argc, char *argv[]){
    int shmid;
    int semid;  //信号灯使用
    pid_t readbuf,writebuf;
    if ((shmid = shmget((key_t)10,sizeof(struct Buffer),0666|IPC_CREAT)<=0)) {
        cout<<"id error"<<endl;
        exit(-1);
    };
    Buffer *buffer = (struct Buffer*)shmat(shmid,NULL,0);
    if ((int64_t)buffer==-1) {
        cout<<"addr error"<<endl;
        exit(-1);
    }
    for (int i = 0; i < buffer_num; i++) {
        int temp = shmget((key_t)(10+i),sizeof(struct Buffer),0666|IPC_CREAT);
        if (temp<=0) {
            cout<<"id error"<<endl;
        }
        buffer->nextshm = temp;
        buffer->size = 0;
        buffer->status = STATUS_PENDING;
        buffer = (struct Buffer*)shmat(shmid,NULL,0);
        if ((int64_t)buffer==-1) {
            cout<<"addr error"<<endl;
        }
    }
    buffer->nextshm = shmid;
    

    //下面创建信号灯
    semid = semget((key_t)252,3,IPC_CREAT|0666);//使用2个信号量
    //N,空闲位置数
    arg.val = buffer_num;
    if(semctl(semid,0,SETVAL,arg)<0){
        cout<<"semctl 0 error!"<<endl;
        exit(0);
    }
    //0,缓冲区已有数据数
    arg.val = 0;
    if(semctl(semid,1,SETVAL,arg)<0){
        cout<<"semctl 1 error!"<<endl;
        exit(0);
    }
    arg.val = 1;
    if(semctl(semid,2,SETVAL,arg)<0){
        cout<<"semctl 2 error!"<<endl;
        exit(0);
    }
    //进程创建
    if((readbuf=fork())==0){
        cout<<"readbuf get created!"<<endl;
        execl("./get","get",argv[2],NULL);
        exit(0);
    }else if((writebuf=fork())==0){
        cout<<"writebuf get created!"<<endl;
        execl("./put","put",argv[1],NULL);
        exit(0);
    }else{  //father
        wait(&readbuf);
        wait(&writebuf);
        semctl(semid,3,IPC_RMID,arg);
        shmctl(shmid,IPC_RMID,NULL);
    }
}
