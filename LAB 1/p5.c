#include <stdio.h>

int main() {
    FILE *fptr;
    char filename[] = "example.txt";
    char content[] = "Hello, this is a test file.";

    // Writing to the file
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fprintf(fptr, "%s", content);
    fclose(fptr);

    // Reading from the file
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    char ch;
    printf("Content of the file:\n");
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);

    return 0;
}
