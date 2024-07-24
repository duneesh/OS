//random access file 13
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void addEmployee(FILE *file);
void viewEmployees(FILE *file);
void searchEmployee(FILE *file, int id);

int main() {
    FILE *file;
    int choice, id;

    file = fopen("employees.dat", "rb+");
    if (file == NULL) {
        file = fopen("employees.dat", "wb+");
        if (file == NULL) {
            printf("Unable to open file.\n");
            exit(1);
        }
    }

    while (1) {
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                viewEmployees(file);
                break;
            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                searchEmployee(file, id);
                break;
            case 4:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addEmployee(FILE *file) {
    Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fseek(file, 0, SEEK_END);
    fwrite(&emp, sizeof(Employee), 1, file);
}

void viewEmployees(FILE *file) {
    Employee emp;
    rewind(file);

    printf("\nEmployee Details:\n");
    printf("ID\tName\t\tSalary\n");
    printf("-------------------------------\n");
    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("%d\t%s\t\t%.2f\n", emp.id, emp.name, emp.salary);
    }
    printf("\n");
}

void searchEmployee(FILE *file, int id) {
    Employee emp;
    rewind(file);
    int found = 0;

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Salary: %.2f\n\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

