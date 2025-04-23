#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define SIZE 100
struct msgbuf {
    long mtype;
    char mtext[SIZE];
};

int
main(int argc, char *argv[])
{
    mqd_t  mqdes;
    unsigned int prio=2;
    char buff[SIZE]={0};
    char nulbuf[SIZE]={0};
    char checkbuff[SIZE]={0};
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = SIZE;
    attr.mq_flags = 0;
    mqdes = mq_open("/my_queue", O_RDWR |O_CREAT, 0600,&attr);
    if (mqdes == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    do{
        if(mq_receive(mqdes, buff, SIZE, &prio)==-1){
            perror("msgrecv");
            exit(EXIT_FAILURE);
        }
        if(prio==255)break;//check input for exit message
        printf("get:%s",buff);

        strcpy(buff,nulbuf);//clear buffer
        strcpy(checkbuff,nulbuf);//clear buffer

        printf("Enter your message:");
        fgets(buff,SIZE,stdin);
        fseek(stdin,0,SEEK_END);

        sscanf(buff,"%s",checkbuff);//check input for "exit"
        if(strcmp(checkbuff,"exit")==0){
            if(mq_send(mqdes,buff,strlen(buff),255)==-1){
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            
            break;
        }
        else{
            if(mq_send(mqdes,buff,strlen(buff),1)==-1){
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
        }
    }while(1);
    if(mq_close(mqdes)==-1){
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    if(mq_unlink("/my_queue")==-1){
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}