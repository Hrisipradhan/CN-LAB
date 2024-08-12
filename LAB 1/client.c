#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    int sockfd;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);//we can specify the predefined marker IPPROTO_UDP
    //int socket(int domain, int type ,int protocol);
    if(sockfd==-1){
        printf("socket creation failure\n");
    }else{
        printf("Socket creation Sucessful\n");
    }
    close(sockfd);
    
    return 0;
}

