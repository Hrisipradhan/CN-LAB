#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Prompt user for the size of the array
    int size;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    // Allocate memory for the array
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Prompt user for the array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Prompt user for the string
    char str[MAXLINE];
    printf("Enter a string: ");
    scanf("%s", str);

    // Send the size of the array to the server
    send(sock, &size, sizeof(int), 0);

    // Send the array to the server
    send(sock, arr, sizeof(int) * size, 0);

    // Send the string to the server
    send(sock, str, sizeof(str), 0);

    printf("Array and string sent to server for sorting.\n");

    // Receive the sorted array from the server
    read(sock, arr, sizeof(int) * size);

    // Receive the sorted string from the server
    read(sock, str, sizeof(str));

    // Print the sorted array
    printf("Sorted array received from server: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Print the sorted string
    printf("Sorted string received from server: %s\n", str);

    // Clean up
    close(sock);
    free(arr);

    return 0;
}
