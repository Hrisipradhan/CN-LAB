#include <stdio.h>

// Define the struct for Employee
struct Employee {
    int emp_id;
    char emp_name[50];
    float bs; // Basic Salary
    float da; // Dearness Allowance
    float ta; // Travel Allowance
    float gp; // Gross Pay
};

// Function to input employee details and calculate allowances
void inputEmployeeDetails(struct Employee *emp) {
    printf("Enter Employee ID: ");
    scanf("%d", &emp->emp_id);
    printf("Enter Employee Name: ");
    scanf("%s", emp->emp_name);
    printf("Enter Basic Salary: ");
    scanf("%f", &emp->bs);

    // Calculate DA, TA, and GP
    emp->da = emp->bs * 0.12;
    emp->ta = emp->bs * 0.10;
    emp->gp = emp->bs + emp->da + emp->ta;
}

// Function to display employee details
void displayEmployeeDetails(struct Employee *emp) {
    printf("\nEmployee ID: %d\n", emp->emp_id);
    printf("Employee Name: %s\n", emp->emp_name);
    printf("Basic Salary: %.2f\n", emp->bs);
    printf("Dearness Allowance (DA): %.2f\n", emp->da);
    printf("Travel Allowance (TA): %.2f\n", emp->ta);
    printf("Gross Pay (GP): %.2f\n", emp->gp);
}

int main() {
    struct Employee emp;

    // Input employee details
    inputEmployeeDetails(&emp);

    // Display employee details
    displayEmployeeDetails(&emp);

    return 0;
}
