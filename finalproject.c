//Final Project
/*
Pablo Mendoza
Samuel Yang
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Numbers that shouldn't change
#define MAX_STUDENTS 100
#define MAX_FACULTY 30
#define GPA_DISCOUNT 3.85
#define CREDITHOUR_COST 236.45
#define FEE 52.00

// This is the student structure
typedef struct {
    char name[50];
    char id[10];
    float gpa;
    int credit_hours;
} Student;

//This is the faculty structure
typedef struct {
    char name[50];
    char id[10];
    char department[20];
    char rank[20];
} Faculty;

Student students[MAX_STUDENTS];
Faculty faculty[MAX_FACULTY];
int student_count = 0, faculty_count = 0;

//This is called to make a string upper case
void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

//This is called in order to check if an ID is in the valid format
int is_valid_id(const char *id) {
    if (strlen(id) != 8) return 0;
    if (!isalpha(id[0]) || !isalpha(id[1])) return 0;
    for (int i = 2; i < 8; i++) {
        if (!isdigit(id[i])) return 0;
    }
    return 1;
}
int is_valid_department(const char *department) {
    return (strcmp(department, "MATH") == 0 || strcmp(department, "CS") == 0 || strcmp(department, "SCIENCE") == 0);
}

int is_valid_rank(const char *rank) {
    return (strcmp(rank, "PROFESSOR") == 0 || strcmp(rank, "ADJUNCT") == 0);
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students.\n");
        return;
    }

    Student new_student;
    printf("Enter the student’s info:\n");
    printf("Name of Student: ");
    getchar(); // this just removes the new line character
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';  // finds the new line character and replaces with the string terminator

    printf("ID: ");
    scanf("%s", new_student.id);
    to_uppercase(new_student.id);

    if (!is_valid_id(new_student.id)) {
        printf("Invalid ID format.\n");
        return;
    }

    printf("Gpa: ");
    scanf("%f", &new_student.gpa);

    printf("Credit hours: ");
    scanf("%d", &new_student.credit_hours);

    students[student_count++] = new_student;
    printf("Thanks!\n");
}
//adds a new faculty member
void add_faculty() {
    if (faculty_count >= MAX_FACULTY) {
        printf("Cannot add more faculty members.\n");
        return;
    }

    Faculty new_faculty;
    int attempts = 0;

    printf("Enter the faculty’s info:\n");
    printf("Name of the faculty: ");
    getchar();
    fgets(new_faculty.name, sizeof(new_faculty.name), stdin);
    new_faculty.name[strcspn(new_faculty.name, "\n")] = '\0';

    printf("ID: ");
    scanf("%s", new_faculty.id);
    to_uppercase(new_faculty.id);

    if (!is_valid_id(new_faculty.id)) {
        printf("Invalid ID format.\n");
        return;
    }

    while (attempts < 3) {
        printf("Rank: ");
        scanf("%s", new_faculty.rank);
        to_uppercase(new_faculty.rank);

        if (is_valid_rank(new_faculty.rank)) {
            break;
        } else {
            attempts++;
            printf("Sorry entered rank (%s) is invalid. Try again.\n", new_faculty.rank);
        }
    }

    if (attempts == 3) {
        printf("You have tried too many times...\n");
        return;
    }

    while (1) {
        printf("Department: ");
        scanf("%s", new_faculty.department);
        to_uppercase(new_faculty.department);

        if (is_valid_department(new_faculty.department)) {
            break;
        } else {
            printf("Invalid department. Valid options: MATH, CS, SCIENCE.\n");
        }
    }

    faculty[faculty_count++] = new_faculty;
    printf("Thanks!\n");
}
// this prints the tution invoice for a student
void print_tuition_invoice() {
    char student_id[10];
    printf("Enter the student’s id: ");
    scanf("%s", student_id);
    to_uppercase(student_id);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, student_id) == 0) {
            Student s = students[i];
            double total_payment = (s.credit_hours * CREDITHOUR_COST) + FEE;

            // This prints the student information
            printf("Here is the tuition invoice for %s:\n", s.name);
            printf("--------------------------------------------------------------------------\n");
            printf("%s %s\n", s.name, s.id);
            printf("Credit Hours: %d ($236.45/credit hour)\n", s.credit_hours);
            printf("Fees: $52\n");

            // This checks if the discount applies
            if (s.gpa >= GPA_DISCOUNT) {
                total_payment *= 0.75;  // This applies a 25% discount
                printf("Total payment: $%.2f (25%% discount applied)\n", total_payment);
            } else {
                printf("Total payment: $%.2f ($0 discount applied)\n", total_payment);
            }

            printf("--------------------------------------------------------------------------\n");
            return;
        }
    }
    printf("Sorry, student not found!\n");
}


//this prints the faculty information
void print_faculty_info() {
    char faculty_id[10];
    printf("Enter the faculty’s id: ");
    scanf("%s", faculty_id);
    to_uppercase(faculty_id);

    for (int i = 0; i < faculty_count; i++) {
        if (strcmp(faculty[i].id, faculty_id) == 0) {
            Faculty f = faculty[i];
            printf("Faculty found:\n");
            printf("---------------------------------------------------------------------------\n");
            printf("%s\n", f.name);
            printf("%s department, %s\n", f.department, f.rank);
            printf("---------------------------------------------------------------------------\n");
            return;
        }
    }
    printf("Sorry %s doesn’t exist\n", faculty_id);
}

int main() {
    int choice;
    while (1) {
        printf("Welcome to PerPro\n");
        printf("Choose one of the options:\n");
        printf("1- Add a new faculty member\n");
        printf("2- Add a new student\n");
        printf("3- Print tuition invoice for a student\n");
        printf("4- Print information of a faculty\n");
        printf("5- Exit Program\n");

        printf("Enter your selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_faculty();
                break;
            case 2:
                add_student();
                break;
            case 3:
                print_tuition_invoice();
                break;
            case 4:
                print_faculty_info();
                break;
            case 5:
                printf("Thank you for using PerPro. Goodbye!\n");
                return 0;
            default:
                printf("Invalid entry- please try again.\n");
        }
    }
}
