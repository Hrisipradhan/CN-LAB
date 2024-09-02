#include<stdio.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    int cs;
    if(cs = socket(AF_INET,SOCK_DGRAM,0)<1){
        printf("coudn't create socket");

    }
    printf("Socket create sucessfully");






}