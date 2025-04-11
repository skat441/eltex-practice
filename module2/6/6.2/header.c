#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
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

typedef struct Node{
    Person* p;
    struct Node* nextP;
    struct Node* prevP;
}Node;

Person* PersonInit(int ID, char* firstname,char* lastname,char isExtraInf, ...){
    Person* newp=malloc(sizeof(Person));
    int fsize=strlen(firstname);
    int lsize=strlen(lastname);
    char* newFname=malloc(fsize+1);
    char* newLname=malloc(lsize+1);
    strncpy(newFname,firstname,fsize);
    strncpy(newLname,lastname,lsize);
    newFname[fsize]=0;
    newLname[lsize]=0;
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
        newp->ExtraInformation=0;
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

Node* getINodeByIndex(Node* head, int index){
    Node* iNode=head;
    for(int i=0;i<index && iNode!=NULL;i++){
        iNode=iNode->nextP;
    }
    return iNode;
}

Node* getINodeById(Node* head, int id){
    Node* iNode=head;
    for(;iNode!=NULL && iNode->p->id!=id;){
        iNode=iNode->nextP;
    }
    return iNode;
}


Node* insertPerson(Node* head, Person* newP){
    if(newP==NULL)return head;
    if(head==NULL){//empty list
        Node* newEl=malloc(sizeof(Node));
        newEl->p=newP;
        newEl->nextP=NULL;
        newEl->prevP=NULL;
        return newEl;
    }
    else if(head->nextP==NULL){//One element in list
        Node* newEl=malloc(sizeof(Node));
        newEl->p=newP;
        if(newP->id>head->p->id){//add to end of list
            newEl->prevP=head;
            newEl->nextP=NULL;
            head->nextP=newEl;
            return head;
        }
        else{//add to begining of list
            newEl->nextP=head;
            newEl->prevP=NULL;
            head->prevP=newEl;
            head->nextP=NULL;
            return newEl;
        }
    }
    else{//elements more then one
        Node* iNode=head;
        Node* tmpNode=NULL;
        for(;iNode!=NULL && newP->id > iNode->p->id;){tmpNode=iNode;iNode=iNode->nextP;}
        if(iNode==NULL){//new Element is last, last element is tmpNode
            Node* newEl=malloc(sizeof(Node));
            newEl->p=newP;
            newEl->nextP=NULL;
            newEl->prevP=tmpNode;
            tmpNode->nextP=newEl;
            return head;
        }
        else if(iNode==head){//new element is first
            Node* newEl=malloc(sizeof(Node));
            newEl->p=newP;
            newEl->prevP=NULL;
            newEl->nextP=head;
            head->prevP=newEl;
            return newEl;
        }
        else{//new element is between elements, left element is tmpNode, right element is iNode
            Node* newEl=malloc(sizeof(Node));
            newEl->p=newP;
            newEl->nextP=iNode;
            newEl->prevP=tmpNode;
            tmpNode->nextP=newEl;
            iNode->prevP=newEl;
            return head;
        }
    }
    return head;
}

void viewList(Node* head){
    if(head==NULL){printf("Phonebook is empty\n");return;}
    //printf("sajmdklajfklfa");
    for(Node* iNode=head;iNode!=NULL;iNode=iNode->nextP){
        if(iNode->p->ExtraInformation==0){
            printf("id:%d\tfirstname:%s lastname:%s\n",iNode->p->id,iNode->p->FirstName,iNode->p->LastName);
        }
        else{
            printf("id:%d\tfirstname:%s lastname:%s phonenumber:%llu E-mail:%s bithdate:%d.%d.%d\n",
            iNode->p->id,iNode->p->FirstName,iNode->p->LastName, iNode->p->PhoneNumber,iNode->p->Email,
            iNode->p->BirthDate.day, iNode->p->BirthDate.month, iNode->p->BirthDate.year);
        }
    }
}


void* clearPhoneBook(Person** phoneBook,int size){
    for(int i=0;i<(size);i++){
        PersonFree(phoneBook[i]);
    }
    free(phoneBook);
    return NULL;
}

Node* clearList(Node* head){
    if(head==NULL)return NULL;
    for(Node* iNode=head;iNode!=NULL;){
        PersonFree(iNode->p);
        Node* tmp=iNode->nextP;
        free(iNode);
        iNode=tmp;
    }
    return NULL;
}

Node* deletePerson(Node* head, int id){
    if(head==NULL)return NULL;
    Node* delNode=getINodeById(head, id);
    if(delNode==NULL)return head;
    else{
        Node* rightNode=delNode->nextP;
        Node* leftNode=delNode->prevP;
        if(rightNode==leftNode){//only one element in list
            PersonFree(delNode->p);
            free (delNode);
            return NULL;
        }
        else if(delNode==head){//del element is head(first)
            PersonFree(head->p);
            head->nextP->prevP=NULL;
            head=head->nextP;
            free(delNode);
            return head;
        }
        else if(delNode->nextP==NULL){//del element is last
            delNode->prevP->nextP=NULL;
            PersonFree(delNode->p);
            free(delNode);
            return head;
        }
        else{//del element is between left and right el
            leftNode->nextP=rightNode;
            rightNode->prevP=leftNode;
            PersonFree(delNode->p);
            free(delNode);
            return head;
        }
    }
    return head;
}

int isContainList(Node* head, int id){
    for(Node* iNode=head;iNode!=NULL;iNode=iNode->nextP){
        if(iNode->p->id==id)return 1;
    }
    return 0;
}

void changePersonList(Node* head, int ID, char fieldToChange, ...){
    int pos;
    Node* changeNode=getINodeById(head,ID);
    va_list args;
    va_start(args,fieldToChange);
    switch (fieldToChange)
    {
    case 1:
        char* Fname=va_arg(args,char*);
        char* newFname=malloc(strlen(Fname)+1);
        strncpy(newFname,Fname,strlen(Fname)+1);
        newFname[strlen(Fname)]=0;
        free(changeNode->p->FirstName);
        changeNode->p->FirstName=newFname;
        break;
    case 2:
        char* Lname=va_arg(args,char*);
        char* newLname=malloc(strlen(Lname)+1);
        strncpy(newLname,Lname,strlen(Lname)+1);
        newLname[strlen(Lname)]=0;
        free(changeNode->p->LastName);
        changeNode->p->LastName=newLname;
        break;
    case 3:
        int ShowExtraInfo=va_arg(args,int);
        changeNode->p->ExtraInformation=ShowExtraInfo;
        break;
    case 4:
        long long newphonenumber=va_arg(args,long long);
        changeNode->p->PhoneNumber=newphonenumber;
        break;
    case 5:
        char* email=va_arg(args,char*);
        char* newemail=malloc(strlen(email)+1);
        strncpy(newemail,email,strlen(email)+1);
        newemail[strlen(email)]=0;
        free(changeNode->p->Email);
        changeNode->p->Email=newemail;
        break;
    case 6:
        Date newDate=va_arg(args,Date);
        changeNode->p->BirthDate.day=newDate.day;
        changeNode->p->BirthDate.month=newDate.month;
        changeNode->p->BirthDate.year=newDate.year;
        break;
    default:
        break;
    }
}
