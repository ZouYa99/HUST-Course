//
//  get.cpp
//  lab3
//
//  Created by ZouYa on 2021/12/23.
//

#include "header.h"

union semun arg;
struct sembuf sem;

int main(int argc, char *argv[]){

    int semid;
    if((semid = semget((key_t)252,3,IPC_CREAT|0666))==-1){
        cout<<"get.cpp semget error!"<<endl;
        exit(2);
    }
    
    FILE* fpw = fopen(argv[1],"w");
    if(fpw==nullptr){
        cout<<"fopen output.txt error!"<<endl;
        exit(2);
    }
    int get = 0;
    while(true){
        P(semid, 2);
        P(semid,0); //缓冲区写入的数的个数
        
        V(semid,1); //缓冲区空余位置数
        V(semid, 2);
    }
    fclose(fpw);
    cout<<"success write to output.txt "<<get<<"bytes"<<endl;
    return 0;

}
