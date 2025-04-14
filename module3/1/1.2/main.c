#include<stdio.h>
#include<unistd.h>
#include <string.h>
#include<stdlib.h>

char** getArgv(){
    char argc[100]={0};
    char buff[100]={0};
    char nulbuf[100]={0};
    char** argv=NULL;
    scanf("%s",argc);
    argv=(char**)calloc(sizeof(char*),(atoi(argc)+2));
    //argv[0]="./sum\0";
    argv[atoi(argc)+1]=NULL;
    char* argbuf=0;
    for (int i = 1; i < atoi(argc)+1; i++)
    {
        strcpy(buff,nulbuf);
        scanf("%s",buff);
        argbuf=(char*)calloc(sizeof(char),strlen(buff)+1);
        strcpy(argbuf,buff);//
        argv[i]=argbuf;
    }
    return argv;
}

int main(){
    char buff[100]={0};
    char nulbuf[100]={0};
    int choose=0;
    printf("List of programms:\n");
    printf("---1.Sum (number of args args)\n");
    printf("---2.Strcat (number of args args)\n");
    printf("---3.Max (number of args args)\n");
    printf("---4.Maxlength (number of args args)\n");
    printf("Your choose:");
    scanf("%s",buff);
    char argc[100]={0};
    if(strcmp(buff,"Sum")==0){
        char** argv=getArgv();
        argv[0]="./sum";
        execvp(argv[0],argv);
        
    }
    else if(strcmp(buff,"Strcat")==0){
        char** argv=getArgv();
        argv[0]="./Strcat";
        execvp(argv[0],argv);
    }
    else if(strcmp(buff,"Max")==0){
        char** argv=getArgv();
        argv[0]="./Max";
        execvp(argv[0],argv);
    }
    else if(strcmp(buff,"Maxlength")==0){
        char** argv=getArgv();
        argv[0]="./Maxlength";
        execvp(argv[0],argv);
    }
    return 0;
}