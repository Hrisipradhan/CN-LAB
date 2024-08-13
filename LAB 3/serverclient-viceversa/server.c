// write a sender and recevier program in c using connectionless socket(UDP) both of them we exchange messages with each other continiously if any 
// one of them will receive the the exit message from the other end then both of them will close the connection.

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main()
{
    int ss, sb;
    char buffer[BUFFER_SIZE];
    ss = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(6011);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(ss, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
    struct sockaddr_in tempsendaddr;
    char buf[100];
    int len = sizeof(struct sockaddr);

    
    while (1) {
        int n = recvfrom(ss, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &tempsendaddr, &len);
        buffer[n] = '\0';
        printf("Recieved from client : %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Sender requested exit. Exiting...\n");
            break;
        }

        printf("Send to Client : ");
        fgets(buffer, BUFFER_SIZE, stdin);

        sendto(ss, buffer, strlen(buffer), 0, (const struct sockaddr *) &tempsendaddr, len);

        
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Receiver exiting...\n");
            break;
        }
    }

    return 0;
}