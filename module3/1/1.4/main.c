#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int rv;
    int n=atoi(argv[1]);
    int fd[2];
    pipe(fd);
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(EXIT_FAILURE);
    }
    else if (p == 0){//child
        close(fd[0]);
        int num;
        srand(time(NULL));
        for(int i=0;i<n;i++){
            num=rand()%256;
            write(fd[1],&num,sizeof(int));
        }
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else{//parent
        close(fd[1]);
        wait(&rv);
        int num;
        printf("Nums:");
        int file=open("save.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
        if(file<0){
            printf("Error to open file");
            return 0;
        }
        else{
            for(int i=0;i<n;i++){
                read(fd[0],&num,sizeof(int));
                write(file,&num,sizeof(int));
                printf("%d ",num);
                
            }
            close(file);
        }
        close(fd[0]);
    }
    printf("\n");
    return 0;
}