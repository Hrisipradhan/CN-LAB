#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

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

    // Prompt user for the key to search
    int key;
    printf("Enter the key to search: ");
    scanf("%d", &key);

    socklen_t len = sizeof(servaddr);

    // Send the size of the array to the server
    sendto(sockfd, &size, sizeof(int), 0, (const struct sockaddr *)&servaddr, len);

    // Send the array to the server
    sendto(sockfd, arr, sizeof(int) * size, 0, (const struct sockaddr *)&servaddr, len);

    // Send the key to the server
    sendto(sockfd, &key, sizeof(int), 0, (const struct sockaddr *)&servaddr, len);

    printf("Array and key sent to server for searching.\n");

    // Receive the position of the key from the server
    int position;
    recvfrom(sockfd, &position, sizeof(int), 0, (struct sockaddr *)&servaddr, &len);

    // Print the result
    if (position == -1) {
        printf("Key not found\n");
    } else {
        printf("Key found at position %d\n", position);
    }

    // Clean up
    close(sockfd);
    free(arr);

    return 0;
}
