#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int rv;
    int size=argc;
    int* arr=(int*)malloc(sizeof(int)*size);
    for(int i=1;i<size;i++)arr[i]=atoi(argv[i]);
    int fd[2];
    pipe(fd);
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(EXIT_FAILURE);
    }
    else if (p == 0){//child
        close(fd[0]);
        for(int i=0;i<size;i++){
            if(i%2==0)arr[i]=arr[i]*arr[i];
        }
        write(fd[1],arr,sizeof(int)*size);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else{//parent
        close(fd[1]);
        for(int i=0;i<size;i++){
            if(i%2!=0)arr[i]=arr[i]*arr[i];
        }
        wait(&rv);
        int num;
        for(int i=0;i<size;i++){
            read(fd[0],&num,sizeof(int));
            if(i%2==0)arr[i]=num;
            
        }
        close(fd[0]);
    }
    for(int i=1;i<size;i++)printf("%d ",arr[i]);
    printf("\n");
    return 0;
}