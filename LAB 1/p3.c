#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Candidate {
    int regdno;
    char name[50];
    char address[100];
    struct Date dob;
};


void input(struct Candidate *c) {
    printf("Enter registration number: ");
    scanf("%d", &c->regdno);
    printf("Enter name: ");
    scanf("%s", c->name);
    printf("Enter address: ");
    scanf(" %[^\n]s", c->address);
    printf("Enter date(day month year): ");
    scanf("%d %d %d", &c->dob.day, &c->dob.month, &c->dob.year);
}


void display(struct Candidate *c) {
    printf("\nRegistration Number: %d\n", c->regdno);
    printf("Name: %s\n", c->name);
    printf("Address: %s\n", c->address);
    printf("Date of Birth: %02d/%02d/%04d\n", c->dob.day, c->dob.month, c->dob.year);
}

int main() {
    struct Candidate c1;

    input(&c1);
    display(&c1);

    return 0;
}