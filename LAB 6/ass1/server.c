#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <arpa/inet.h>  

#define PORT 8080  
#define MAX_STUDENTS 5  
#define BUFFER_SIZE 256  

typedef struct {  
    int roll_no;  
    char name[50];  
    float percentage;  
} Student;  

Student students[MAX_STUDENTS] = {  
    {1, "Alice", 85.5},  
    {2, "Bob", 90.0},  
    {3, "Charlie", 78.0},  
    {4, "David", 88.5},  
    {5, "Eve", 92.0}  
};  

void handle_client(int client_socket) {  
    int roll_no;  
    char buffer[BUFFER_SIZE];  


    recv(client_socket, &roll_no, sizeof(roll_no), 0);  
    

    int found = 0;  
    for (int i = 0; i < MAX_STUDENTS; i++) {  
        if (students[i].roll_no == roll_no) {  
            snprintf(buffer, sizeof(buffer), "Roll No: %d, Name: %s, Percentage: %.2f%%",   
                     students[i].roll_no, students[i].name, students[i].percentage);  
            found = 1;  
            break;  
        }  
    }  

    if (!found) {  
        snprintf(buffer, sizeof(buffer), "Record toh yanha nahil hai bc");  
    }  

 
    send(client_socket, buffer, strlen(buffer), 0);  
    close(client_socket);  
}  

int main() {  
    int server_socket, client_socket;  
    struct sockaddr_in server_addr, client_addr;  
    socklen_t addr_size = sizeof(client_addr);  


    server_socket = socket(AF_INET, SOCK_STREAM, 0);  
    if (server_socket < 0) {  
        perror("Socket nahi bana hai");  
        exit(EXIT_FAILURE);  
    }  


    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = INADDR_ANY;  
    server_addr.sin_port = htons(PORT);  

 
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));  
    listen(server_socket, 5);  

    printf("Server sunn rha hai..\n");  

    while (1) {  

        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);  
        printf("Client connected.\n");  
        handle_client(client_socket);  
    }  

    close(server_socket);  
    return 0;  
}