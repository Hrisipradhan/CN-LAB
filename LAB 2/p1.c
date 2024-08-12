#include<stdio.h>
void swap(int*a,int*b){
    int temp = *a;
    *a=*b;
    *b=temp;
}

int main(){
    int x;
    int y;
    printf("Enter two numbers :");
    scanf("%d %d",&x,&y);
    printf("Before swap %d %d\n",x,y);
    swap(&x,&y);
    printf("After swap %d %d\n",x,y);
    
    
    return 0;
}