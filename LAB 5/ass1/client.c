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

    // Prompt user for the string
    char str[MAXLINE];
    printf("Enter a string: ");
    scanf("%s", str);

    // Send the size to the server
    sendto(sockfd, &size, sizeof(int), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    // Send the array to the server
    sendto(sockfd, arr, sizeof(int) * size, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    // Send the string to the server
    sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Array and string sent to server for sorting.\n");

    // Receive the sorted array from the server
    int n, len;
    len = sizeof(servaddr);
    recvfrom(sockfd, arr, sizeof(int) * size, 0, (struct sockaddr *)&servaddr, &len);

    // Receive the sorted string from the server
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&servaddr, &len);

    // Print the sorted array
    printf("Sorted array received from server: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Print the sorted string
    printf("Sorted string received from server: %s\n", str);

    // Clean up
    close(sockfd);
    free(arr);

    return 0;
}
