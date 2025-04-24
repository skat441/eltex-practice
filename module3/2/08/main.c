#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/sem.h>

union semun {
    int val; /* значение для SETVAL */
    struct semid_ds *buf; /* буферы для IPC_STAT, IPC_SET */
    unsigned short *array; /* массивы для GETALL, SETALL */
    /* часть, особенная для Linux: */
    struct seminfo *__buf; /* буфер для IPC_INFO */
    };

void pause_child(){
    pause();
    return;
}

void continue_child(){
    return;
}

int main(int argc, char *argv[])
{
    union semun arg;
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if(semid==-1){
        perror("semget");
        exit(EXIT_FAILURE);
    }
    /*Установить в семафоре No 0 (Контроллер ресурсов) значение "1"*/
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    struct sembuf unlock= {0, 1, SEM_UNDO};
    struct sembuf lock = {0, -1, SEM_UNDO};
    //
    int n=atoi(argv[1]);
    int fd[2];
    pipe(fd);
    pid_t p = fork();//get child PID
    if(p<0){
      perror("fork fail");
      exit(EXIT_FAILURE);
    }
    else if (p == 0){//child
        int file=open("save.txt",O_RDWR,0777);
        close(fd[0]);
        int num;
        int num_file=0;
        srand(time(NULL));
        printf("Nums:");
        sleep(1);
        for(int i=0;i<n;i++){
            num=rand()%256;
            write(fd[1],&num,sizeof(int));
            semop(semid,&lock,1);
            read(file,&num_file,sizeof(int));
            semop(semid,&unlock,1);
            printf("%d ",num_file);
            fflush(stdout);
        }
        printf("\n");
        close(fd[1]);
        close(file);
        exit(EXIT_SUCCESS);
    }
    else{//parent
        close(fd[1]);
        //wait(&rv);
        int num;
        //printf("Nums:");
        int file=open("save.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
        if(file<0){
            printf("Error to open file");
            return 0;
        }
        else{
            for(int i=0;i<n;i++){
                //sleep(0.1);
                semop(semid,&lock,1);
                read(fd[0],&num,sizeof(int));
                write(file,&num,sizeof(int));
                semop(semid,&unlock,1);
                //printf("%d ",num);
                
            }
            close(file);
        }
        close(fd[0]);
    }
    semctl(semid, 0, IPC_RMID);
    return 0;
}