#include <stdio.h>
#include "header.h"
int main(){
    char answer=0;
    int a,b;
    double c,d;
    int result;
    double fresult;
    while(answer!=-1){
        printf("\n1-sum\n2-neg\n3-mult\n4-div\n5-mod\n-1-exit\nEnter option:");
        scanf("%d",&answer);
        fseek(stdin,0,SEEK_END);
        switch (answer)
        {
        case 1:
            printf("Enter first operand:");
            scanf("%d",&a);
            printf("Enter second operand:");
            scanf("%d",&b);
            result=sum(a,b);
            printf("Result is:%d",result);
            break;
        case 2:
            printf("Enter first operand:");
            scanf("%d",&a);
            printf("Enter second operand:");
            scanf("%d",&b);
            result=neg(a,b);
            printf("Result is:%d",result);
            break;
        case 3:
            printf("Enter first operand:");
            scanf("%d",&a);
            printf("Enter second operand:");
            scanf("%d",&b);
            result=mult(a,b);
            printf("Result is:%d",result);
            break;
        case 4:
            printf("Enter first operand:");
            scanf("%d",&c);
            printf("Enter second operand:");
            scanf("%d",&d);
            fresult=div(c,d);
            printf("Result is:%.2f",fresult);
            break;
        case 5:
            printf("Enter first operand:");
            scanf("%d",&a);
            printf("Enter second operand:");
            scanf("%d",&b);
            result=mod(a,b);
            printf("Result is:%d",result);
            break;
        default:
            answer=-1;
        }
    }
    return 0;
}
