#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <arpa/inet.h>  

#define PORT 8080  
#define BUFFER_SIZE 256  

int main() {  
    int client_socket;  
    struct sockaddr_in server_addr;  
    char buffer[BUFFER_SIZE];  
    int roll_no;  


    client_socket = socket(AF_INET, SOCK_STREAM, 0);  
    if (client_socket < 0) {  
        perror("Socket hie creation nahi hau hai");  
        exit(EXIT_FAILURE);  
    }  


    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server_addr.sin_port = htons(PORT);  


    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {  
        perror("Connection hau failed");  
        exit(EXIT_FAILURE);  
    }  


    printf("Kripiya karke roll number Enter kijye: ");  
    scanf("%d", &roll_no);  

    send(client_socket, &roll_no, sizeof(roll_no), 0);  


    recv(client_socket, buffer, sizeof(buffer), 0);  
    printf("Server ka response: %s\n", buffer);  

    close(client_socket);  
    return 0;  
}