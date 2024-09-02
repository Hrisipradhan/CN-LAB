#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
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
    int arr[MAXLINE];
    int size;
    int key;
    int position = -1; // -1 indicates not found

    len = sizeof(cliaddr);

    // Receive the size of the array
    n = recvfrom(sockfd, &size, sizeof(int), 0, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }

    // Receive the array
    n = recvfrom(sockfd, arr, sizeof(int) * size, 0, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }

    // Receive the key to search
    n = recvfrom(sockfd, &key, sizeof(int), 0, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }

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
    sendto(sockfd, &position, sizeof(int), 0, (const struct sockaddr *)&cliaddr, len);
    if (position == -1) {
        printf("Key not found in the array.\n");
    } else {
        printf("Key found at position %d.\n", position);
    }

    close(sockfd);
    return 0;
}
