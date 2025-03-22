#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
typedef struct Date
{
    char day;
    char month;
    short year;
}Date;

typedef struct Person
{
    int id;
    char* FirstName;
    char* LastName;
    char ExtraInformation;
    long long PhoneNumber;
    char* Email;
    Date BirthDate;
}Person;

Person* PersonInit(int ID, char* firstname,char* lastname,char isExtraInf, ...){
    Person* newp=malloc(sizeof(Person));
    int fsize=strlen(firstname);
    int lsize=strlen(lastname);
    char* newFname=malloc(fsize);
    char* newLname=malloc(lsize);
    strncpy(newFname,firstname,fsize);
    strncpy(newLname,lastname,lsize);
    newp->id=ID;
    newp->FirstName=newFname;
    newp->LastName=newLname;
    if(isExtraInf){
        va_list args;
        va_start(args,isExtraInf);
        long long phonenumber=va_arg(args,long long);
        char* email=va_arg(args, char*);
        Date date=va_arg(args,Date);
        newp->BirthDate=date;
        newp->PhoneNumber=phonenumber;
        if(email!=NULL){
            int esize=strlen(email);
            char* newEmail=malloc(esize);
            strncpy(newEmail,email,esize);
            newp->Email=newEmail;
        }
        else{
            newp->Email=NULL;
        }
        va_end(args);
    }
    else{
        newp->PhoneNumber=0;
        newp->Email=NULL;
        newp->BirthDate.day=0;
        newp->BirthDate.month=0;
        newp->BirthDate.year=0;
    }
    return newp;
}

void* PersonFree(Person* p){
    free(p->FirstName);
    free(p->LastName);
    if(p->Email!=NULL)free(p->Email);
    free(p);
    return NULL;
}

Person** AddContact(Person** phoneBook, int* size, Person* newP){
    (*size)++;
    Person** newPhoneBook=malloc(sizeof(Person*) * (*size));
    for(int i=0;i<((*size)-1);i++){
        newPhoneBook[i]=phoneBook[i];
    }
    newPhoneBook[((*size)-1)]=newP;
    free(phoneBook);
    return newPhoneBook;
}

void viewPhoneBook(Person** phoneBook, int size){
    if((size)==0){printf("Phonebook is empty\n");return;}
    for(int i=0;i<size;i++){
        printf("id:%d\tfirstname:%s lastname:%s\n",phoneBook[i]->id,phoneBook[i]->FirstName,phoneBook[i]->LastName);
    }
}

Person** deleteContact(Person** phoneBook,int* size,int ID){
    (*size)--;
    Person** newPhoneBook=malloc(sizeof(Person*) * (*size));
    int j=0;
    for(int i=0;i<((*size)+1);i++){
        if(phoneBook[i]->id!=ID){newPhoneBook[j]=phoneBook[i];j++;}
        else{phoneBook[i]=PersonFree(phoneBook[i]);}
    }
    free(phoneBook);
    return newPhoneBook;
}
int isContain(Person** phoneBook,int* size,int ID){
    int isfound=0;
    for(int i=0;i<(*size);i++){
        if(phoneBook[i]->id==ID){
            isfound=1;
        }
    }
    return isfound;
}
void changePerson(Person** phoneBook,int size, int ID, char* firstname,char* lastname){
    int pos;
    for(int i=0;i<(size);i++){
        if(phoneBook[i]->id==ID){
            pos=i;
        }
    }
    Person* newP=PersonInit(ID,firstname,lastname,0);
    phoneBook[pos]=PersonFree(phoneBook[pos]);
    phoneBook[pos]=newP;
}
void* clearPhoneBook(Person** phoneBook,int size){
    for(int i=0;i<(size);i++){
        PersonFree(phoneBook[i]);
    }
    free(phoneBook);
    return NULL;
}
