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


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));


    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;


    int size;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }


    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }


    char str[MAXLINE];
    printf("Enter a string: ");
    scanf("%s", str);


    sendto(sockfd, &size, sizeof(int), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));


    sendto(sockfd, arr, sizeof(int) * size, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));


    sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Array and string sent to server for sorting.\n");


    int n, len;
    len = sizeof(servaddr);
    recvfrom(sockfd, arr, sizeof(int) * size, 0, (struct sockaddr *)&servaddr, &len);

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&servaddr, &len);

    printf("Sorted array received from server: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");


    printf("Sorted string received from server: %s\n", str);


    close(sockfd);
    free(arr);

    return 0;
}
