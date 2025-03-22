#include <stdio.h>
#include "header.h"

int main(){
    // Date d;
    //d.day=21;
    //d.month=3;
    //d.year=2025;
    //Person* p = PersonInit(1,"Fralov\0","Pavel\0",1, 79841103791, "knovopashen44@gmail.com", d);
    //printf("new person is:%s %s %d %llu %s %d-%d-%d\n",p->FirstName,p->LastName,p->id,p->PhoneNumber,p->Email,p->BirthDate.day,p->BirthDate.month,p->BirthDate.year);
    //p=PersonFree(p);
    //printf("%d\n",p);
    //int num=0;
    //scanf("%d",&num);
    //printf("%d\n",num);
    Person** phoneBook=malloc(sizeof(Person*));
    Person* p2 = PersonInit(1,"Grimov\0","Alex\0",0);
    //phoneBook[0]=p;
    //phoneBook[1]=p2;
    // for(int i=0;i<2;i++){
    //     printf("new person is:%s %s %d %llu %s %d-%d-%d\n",phoneBook[i]->FirstName,phoneBook[i]->LastName,phoneBook[i]->id,phoneBook[i]->PhoneNumber,phoneBook[i]->Email,phoneBook[i]->BirthDate.day,phoneBook[i]->BirthDate.month,phoneBook[i]->BirthDate.year); 
    // }
    //phoneBook[1]=PersonFree(phoneBook[1]);
    // printf("old ptr:%d\n",phoneBook);
    // phoneBook=AddContact(phoneBook,&phoneBookSize,p);
    // printf("new ptr:%d\n",phoneBook);
    // phoneBook=AddContact(phoneBook,&phoneBookSize,p2);
    // printf("new person is:%s %s %d %llu %s %d-%d-%d\n",phoneBook[1]->FirstName,phoneBook[0]->LastName,phoneBook[0]->id,phoneBook[0]->PhoneNumber,phoneBook[0]->Email,phoneBook[0]->BirthDate.day,phoneBook[0]->BirthDate.month,phoneBook[0]->BirthDate.year); 
    // printf("%d\n\n",phoneBookSize);
    int id=1;
    int ID;
    char isfound;
    char answer=0;
    char buffer[100]={0};
    char fname[100]={0};
    char lname[100]={0};
    char nul[100]={0};
    int phoneBookSize=0;
    while(answer!=-1){
        strncpy(buffer,nul,100);
        strncpy(fname,nul,100);
        strncpy(lname,nul,100);
        printf("\n0-Add Contact to Phonebook\n1-Delete Contact by id\n2-Change Person by id\n3-View Phonebook\n-1-exit\nEnter option:");
        scanf("%d",&answer);
        fseek(stdin,0,SEEK_END);
        switch (answer)
        {
        case 0:
            printf("Enter Person Firstname:");
            scanf("%s",buffer);
            strncpy(fname,buffer,strlen(buffer));
            printf("Enter Person Lastname:");
            scanf("%s",buffer);
            strncpy(lname,buffer,strlen(buffer));
            Person* newP = PersonInit(id,fname,lname,0);
            id++;
            //printf("%d",phoneBookSize);
            phoneBook=AddContact(phoneBook,&phoneBookSize,newP);
            //printf("%d",phoneBookSize);
            break;
        case 1:
            ID=0;
            isfound=0;
            printf("Enter person id:");
            scanf("%d",&ID);
            fseek(stdin,0,SEEK_END);
            //
            isfound=isContain(phoneBook,&phoneBookSize,ID);
            //
            if(!isfound){
                printf("\nPerson with id=%d not found!!!\n",ID);
            }
            else{
                //
                phoneBook=deleteContact(phoneBook,&phoneBookSize,ID);
                //
                printf("\nPerson with id=%d deleted!!!\n",ID);
            }
            break;
        case 2:
            ID=0;
            isfound=0;
            printf("Enter person id:");
            scanf("%d",&ID);
            fseek(stdin,0,SEEK_END);
            //
            isfound=isContain(phoneBook,&phoneBookSize,ID);
            //
            if(!isfound){
                printf("\nPerson with id=%d not found!!!\n",ID);
            }
            else{
                //phoneBook=deleteContact(phoneBook,&phoneBookSize,ID);
                printf("Enter Person Firstname:");
                scanf("%s",buffer);
                strncpy(fname,buffer,strlen(buffer));
                printf("Enter Person Lastname:");
                scanf("%s",buffer);
                strncpy(lname,buffer,strlen(buffer));
                //
                changePerson(phoneBook,phoneBookSize,ID,fname,lname);
                //
                printf("\nPerson with id=%d changed!!!\n",ID);
            }
            break;
        case 3:
            //
            viewPhoneBook(phoneBook,phoneBookSize);
            //
            break;
        default:
            answer=-1;
            //
            phoneBook=clearPhoneBook(phoneBook,phoneBookSize);
            //
        }
    }
    return 1;
}
