#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024
#define MAX_ARRAY_SIZE 100 // Define a maximum size for the array

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Prompt user for the size of the array
    int size;
    printf("Enter the number of elements in the array (max %d): ", MAX_ARRAY_SIZE);
    scanf("%d", &size);

    if (size > MAX_ARRAY_SIZE) {
        printf("Size exceeds maximum allowed size of %d.\n", MAX_ARRAY_SIZE);
        close(sock);
        return -1;
    }

    // Declare a fixed-size array
    int arr[MAX_ARRAY_SIZE];

    // Prompt user for the array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Prompt user for the key to search
    int key;
    printf("Enter the key to search: ");
    scanf("%d", &key);

    // Send the size of the array to the server
    send(sock, &size, sizeof(int), 0);

    // Send the array to the server
    send(sock, arr, sizeof(int) * size, 0);

    // Send the key to the server
    send(sock, &key, sizeof(int), 0);

    printf("Array and key sent to server for searching.\n");

    // Receive the position of the key from the server
    int position;
    read(sock, &position, sizeof(int));

    // Print the result
    if (position == -1) {
        printf("Key not found\n");
    } else {
        printf("Key found at position %d\n", position);
    }

    // Clean up
    close(sock);

    return 0;
}
