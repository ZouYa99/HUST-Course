//
//  main.cpp
//  experiment1
//
//  Created by ZouYa on 2021/12/10.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<iostream>
#include<signal.h>

#define MAX_SEND 10

using namespace std;
int pipefd[2];
pid_t p1,p2;
//分别定义总消息以及各自进程的消息数
int x = 1,x1 = 0,x2 = 0;

void main_handle(int sig){
    kill(p1,SIGUSR1);
    kill(p2,SIGUSR2);

    printf("\nparent send %d times",x);
    cout <<endl<< "Parent Process is Killed!"<<endl;
    exit(0);
}
void p1_handle(int sig){
    cout<<endl<<"child1 received "<<x1<<" times!";
    cout<<endl<<"Child Process 1 is Killed by Parent!";
    exit(0);
}
void p2_handle(int sig){
    cout<<endl<<"child2 received "<<x2<<" times!";
    cout<<endl<<"Child Process 2 is Killed by Parent!"<<endl;
    exit(0);
}

int main(){
    char buffer1[BUFSIZ],buffer2[BUFSIZ];
    pipe(pipefd);
    signal(SIGINT,main_handle);
    cout<<"Seting: the max send times is "<<MAX_SEND<<endl;
    if((p1=fork())==0){  //child1
        close(pipefd[1]);
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1,p1_handle);
        while(1){
            read(pipefd[0],buffer1,BUFSIZ);
            cout<<"child1 receive:"<<buffer1<<endl;
            x1++;
        }
    }else if((p2=fork())==0){  //child2
        close(pipefd[1]);
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR2,p2_handle);
        while(1){
            read(pipefd[0],buffer2,BUFSIZ);
            cout<<"child2 receive:"<<buffer2<<endl;
            x2++;
        }
    }else{   //father
        close(pipefd[0]);
        while(x<MAX_SEND){
            string str = to_string(x);
            write(pipefd[1],str.data(),strlen(str.data()));
            x++;
            sleep(1);
        }
        kill(p1,SIGINT);
        kill(p2,SIGINT);

        kill(p1,SIGUSR1);
        kill(p2,SIGUSR2);

        printf("parent send %d times\n",x);
        cout<<"the send times is at the upper limit,parent process exit"<<endl;
    }
}
