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
    printf("sent: %s\n", msg.mtext);
}

int
main(int argc, char *argv[])
{
    int  qid, opt;
    int  msgtype = 1;
    int  msgkey = 1111;
    char answer=0;
    char buff[SIZE]={0};
    char nulbuf[SIZE]={0};
    do{
        printf("q. exit\n");   
        printf("1. send message\n");   
        printf("2. recive all messages\n");
        printf("Your choose:");
        fgets(buff,SIZE,stdin);
        fseek(stdin,0,SEEK_END);//clear stdin
        sscanf(buff,"%c",&answer);
        strcpy(buff,nulbuf);//clear buffer
        switch (answer)
        {
        case  '1':
            printf("Enter your message:");
            fgets(buff,SIZE,stdin);
            fseek(stdin,0,SEEK_END);
            qid = msgget(msgkey, IPC_CREAT | 0666);
            if (qid == -1) {
                perror("msgget");
                exit(EXIT_FAILURE);
            }
            send_msg(qid,msgtype,buff);
            break;
        case '2':
            struct msgbuf msg;
            strcpy(msg.mtext,nulbuf);
            qid = msgget(msgkey, IPC_CREAT | 0666);
            if (qid == -1) {
                perror("msgget");
                exit(EXIT_FAILURE);
            }
            while(msgrcv(qid, &msg, sizeof(msg.mtext), 2,IPC_NOWAIT) != -1){
                printf("%s",msg.mtext);
                strcpy(msg.mtext,nulbuf);
            }
            if(msgrcv(qid, &msg, sizeof(msg.mtext), 255,IPC_NOWAIT) != -1)exit(EXIT_SUCCESS);
            break;
        case 'q':
            qid = msgget(msgkey, IPC_CREAT | 0666);
            if (qid == -1) {
                perror("msgget");
                exit(EXIT_FAILURE);
            }
            strcpy(buff,"exit");
            send_msg(qid,255,buff);
            break;
        default:
            break;
        }
    }while(answer != 'q');
    exit(EXIT_SUCCESS);
}