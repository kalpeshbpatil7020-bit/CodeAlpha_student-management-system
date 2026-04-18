#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char name[50];
    float marks;
};

// Function to open file safely
FILE* openFile(const char *filename, const char *mode) {
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    return fp;
}

void addStudent() {
    struct student s;
    FILE *fp = openFile("students.dat", "ab");

    printf("\nEnter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct student), 1, fp);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct student s;
    FILE *fp = openFile("students.dat", "rb");

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(struct student), 1, fp)) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int id, found = 0;
    struct student s;
    FILE *fp = openFile("students.dat", "rb");

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.id == id) {
            printf("Found: ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    int id, found = 0;
    struct student s;
    FILE *fp = openFile("students.dat", "rb+");

    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);

            printf("Record Updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    int id, found = 0;
    struct student s;

    FILE *fp = openFile("students.dat", "rb");
    FILE *temp = openFile("temp.dat", "wb");

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(struct student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Student Not Found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}