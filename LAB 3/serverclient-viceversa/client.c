#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main()
{
    int cs, bs;
    char buffer[BUFFER_SIZE];
    cs = socket(AF_INET, SOCK_DGRAM, 0);


    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6011);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");


    while (1) {
        printf("Sender: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        
        sendto(cs, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, sizeof(struct sockaddr));
        int len = sizeof(struct sockaddr);

        
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Sender exiting...\n");
            break;
        }

        int n = recvfrom(cs, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &server, &len);
        buffer[n] = '\0';
        printf("Receiver: %s", buffer);

        
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Receiver requested exit. Exiting...\n");
            break;
        }
    }

    close(cs);
}