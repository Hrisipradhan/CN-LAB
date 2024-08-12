#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {


    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int sum = num1 + num2;

    printf("Sum of %d and %d is: %d\n", num1, num2, sum);

    return 0;
}
