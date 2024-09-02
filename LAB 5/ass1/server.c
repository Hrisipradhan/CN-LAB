#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort algorithm to sort the integer array
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to sort a string alphabetically
void sortString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int n, len;
    int arr[100];
    char str[MAXLINE];
    int size;

    // Receive the size of the array
    len = sizeof(cliaddr);
    recvfrom(sockfd, &size, sizeof(int), 0, (struct sockaddr *)&cliaddr, &len);

    // Receive the array
    recvfrom(sockfd, arr, sizeof(int) * size, 0, (struct sockaddr *)&cliaddr, &len);

    // Receive the string
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&cliaddr, &len);

    // Sort the array
    bubbleSort(arr, size);

    // Sort the string
    sortString(str);

    // Send the sorted array back to the client
    sendto(sockfd, arr, sizeof(int) * size, 0, (const struct sockaddr *)&cliaddr, len);

    // Send the sorted string back to the client
    sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr *)&cliaddr, len);

    printf("Sorted array and string sent back to client.\n");

    close(sockfd);
    return 0;
}
