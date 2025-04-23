#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void pause_child(){
    pause();
    return;
}

void continue_child(){
    return;
}

int main(int argc, char *argv[])
{
    int rv;
    int n=atoi(argv[1]);
    int fd[2];
    pipe(fd);
    pid_t p = fork();//get child PID
    if(p<0){
      perror("fork fail");
      exit(EXIT_FAILURE);
    }
    else if (p == 0){//child
        signal(SIGUSR1,pause_child);
        signal(SIGUSR2,continue_child);
        int file=open("save.txt",O_RDWR,0777);
        close(fd[0]);
        int num;
        int num_file=0;
        srand(time(NULL));
        printf("Nums:");
        for(int i=0;i<n;i++){
            num=rand()%256;
            write(fd[1],&num,sizeof(int));
            sleep(1);
            read(file,&num_file,sizeof(int));
            printf("%d ",num_file);
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
                sleep(0.1);
                read(fd[0],&num,sizeof(int));
                kill(p,SIGUSR1);
                write(file,&num,sizeof(int));
                kill(p,SIGUSR2);
                //printf("%d ",num);
                
            }
            close(file);
        }
        close(fd[0]);
    }
    printf("\n");
    return 0;
}