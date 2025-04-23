#include<stdio.h>
#include<unistd.h>
#include <string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 100
char** getArgv(char buff[SIZE]){
    char argc[SIZE]={0};
    char buff2[SIZE]={0};
    char nulbuf[SIZE]={0};
    char** argv=NULL;
    sscanf(buff,"%s %s",buff2,argc);
    argv=(char**)calloc(sizeof(char*),(atoi(argc)+2));
    argv[atoi(argc)+1]=NULL;
    char* argbuf=strtok(buff," ");//=./
    argbuf=strtok(NULL," ");//=argc
    char *buff3;
    for (int i = 1; i < atoi(argc)+1; i++)
    {
        strcpy(buff2,nulbuf);
        buff3=strtok(NULL," ");
        argbuf=(char*)calloc(sizeof(char),strlen(buff3)+1);
        strcpy(argbuf,buff3);//
        argv[i]=argbuf;
    }
    return argv;
}

int main(){
    char buff[SIZE]={0};
    char buff2[SIZE]={0};
    char nulbuf[SIZE]={0};
    do{
        strcpy(buff,nulbuf);
        printf(">>");
        fgets(buff,SIZE,stdin);
        sscanf(buff,"%s",buff2);
        char argc[SIZE]={0};
        pid_t p = fork();
        if(p<0){
            perror("fork fail");
            exit(EXIT_FAILURE);
        }
        else if(p == 0){//child with
            if(strcmp(buff2,"Sum")==0){
                char** argv=getArgv(buff);
                argv[0]="./sum";
                execvp(argv[0],argv);
                
            }
            else if(strcmp(buff2,"Strcat")==0){
                char** argv=getArgv(buff);
                argv[0]="./Strcat";
                execvp(argv[0],argv);
            }
            else if(strcmp(buff2,"Max")==0){
                char** argv=getArgv(buff);
                argv[0]="./Max";
                execvp(argv[0],argv);
            }
            else if(strcmp(buff2,"Maxlength")==0){
                char** argv=getArgv(buff);
                argv[0]="./Maxlength";
                execvp(argv[0],argv);
            }
            else if(strcmp(buff2,"bush")==0){
                char* argv[]={"./bush",NULL};
                execvp(argv[0],argv);
            }
            exit(EXIT_SUCCESS);
        }
        else{//Parent
            wait(NULL);
        }
    }while(strcmp(buff2,"q")!=0);
    return 0;
}