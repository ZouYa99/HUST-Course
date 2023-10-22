//
//  put.cpp
//  lab3
//
//  Created by ZouYa on 2021/12/23.
//

#include "header.h"

union semun arg;
struct sembuf sem;

int main(int argc, char *argv[]){

    int semid;
    if((semid = semget((key_t)252,3,IPC_CREAT|0666))==-1){  //获取信号量
        printf("get.cpp semget error!\n");
        exit(0);
    }

    FILE* fpr=NULL;
    fpr = fopen(input_addr,"r");
    if(fpr==NULL){
        printf("fopen input.txt error!\n");
        exit(0);
    }
    int put = 0;
    while(true){
        P(semid,0); //缓冲区空余位置数
        auto size = fread(pin->data, 1, buffer_size, fpr);
        pin->size = size;
        put+=size;
        if(size==0){
            break;
        }
        pin=pin->next;
        V(semid,1); //缓冲区已写入数
    }
    fclose(fpr);
    cout<<"success put from input.txt "<<put<<" bytes"<<endl;
    return 0;

}
