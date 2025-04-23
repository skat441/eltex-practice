#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define SIZE 100
struct msgbuf {
    long mtype;
    char mtext[SIZE];
};

static void
send_msg(int qid, int msgtype, char buff[SIZE])
{
    struct msgbuf  msg;
    msg.mtype = msgtype;
    strcpy(msg.mtext,buff);

    if (msgsnd(qid, &msg, sizeof(msg.mtext),0) == -1)
    {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }
}

int
main(int argc, char *argv[])
{
    int  qid, opt;
    int  msgkey = 2222;
    char answer=0;
    char buff[SIZE]={0};
    char nulbuf[SIZE]={0};
    char checkbuff[SIZE]={0};
    qid = msgget(msgkey, IPC_CREAT | 0666);
    if (qid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    do{
        struct msgbuf msg;

        if(msgrcv(qid, &msg, sizeof(msg.mtext), 1,0)==-1){
            perror("msgrecv");
            exit(EXIT_FAILURE);
        }
        if(msgrcv(qid, &msg, sizeof(msg.mtext), 255,IPC_NOWAIT) != -1)exit(EXIT_SUCCESS);//check input for exit message
        printf("get:%s",msg.mtext);
        strcpy(buff,nulbuf);//clear buffer
        strcpy(checkbuff,nulbuf);//clear buffer
        printf("Enter your message:");
        fgets(buff,SIZE,stdin);
        fseek(stdin,0,SEEK_END);
        sscanf(buff,"%s",checkbuff);
        if(strcmp(checkbuff,"exit")==0){
            send_msg(qid,2,buff);
            send_msg(qid,255,buff);
            break;
        }
        else{
            send_msg(qid,2,buff);
        }
    }while(1);
    exit(EXIT_SUCCESS);
}