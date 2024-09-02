#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attach socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    int arr[MAXLINE];
    int size;
    int key;
    int position = -1; // -1 indicates not found

    // Receive the size of the array
    read(new_socket, &size, sizeof(int));

    // Receive the array
    read(new_socket, arr, sizeof(int) * size);

    // Receive the key to search
    read(new_socket, &key, sizeof(int));

    // Print the received array
    printf("Received array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if (arr[i] == key) {
            position = i;
        }
    }
    printf("\n");

    // Send the position of the key back to the client
    send(new_socket, &position, sizeof(int), 0);

    if (position == -1) {
        printf("Key not found in the array.\n");
    } else {
        printf("Key found at position %d.\n", position);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
