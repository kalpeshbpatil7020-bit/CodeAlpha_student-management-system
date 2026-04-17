#include <stdio.h>

#define SIZE 10

// Read matrix
void read(int mat[SIZE][SIZE], int *row, int *col) {
    int i, j;
    printf("Enter rows and columns: ");
    scanf("%d%d", row, col);

    printf("Enter elements:\n");
    for(i = 0; i < *row; i++) {
        for(j = 0; j < *col; j++) {
            scanf("%d", (*(mat + i) + j));
        }
    }
}

// Print matrix
void print(int mat[SIZE][SIZE], int row, int col) {
    int i, j;
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            printf("%d ", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

// Matrix Addition
void sum(int A[SIZE][SIZE], int B[SIZE][SIZE], int row, int col) {
    int i, j, C[SIZE][SIZE];

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("Addition Result:\n");
    print(C, row, col);
}

// Matrix Multiplication
void product(int A[SIZE][SIZE], int B[SIZE][SIZE], int r1, int c1, int c2) {
    int i, j, k, C[SIZE][SIZE];

    for(i = 0; i < r1; i++) {
        for(j = 0; j < c2; j++) {
            C[i][j] = 0;
            for(k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Multiplication Result:\n");
    print(C, r1, c2);
}

// Matrix Transpose
void transpose(int mat[SIZE][SIZE], int row, int col) {
    int i, j, T[SIZE][SIZE];

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            T[j][i] = mat[i][j];
        }
    }

    printf("Transpose:\n");
    print(T, col, row);
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE];
    int r1, c1, r2, c2, ch;

    do {
        printf("\n--- MATRIX OPERATIONS ---\n");
        printf("1. Addition\n2. Multiplication\n3. Transpose\n4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);

        if(ch == 1) {
            printf("Enter Matrix A:\n");
            read(A, &r1, &c1);

            printf("Enter Matrix B:\n");
            read(B, &r2, &c2);

            if(r1 == r2 && c1 == c2)
                sum(A, B, r1, c1);
            else
                printf("Addition not possible!\n");
        }
        else if(ch == 2) {
            printf("Enter Matrix A:\n");
            read(A, &r1, &c1);

            printf("Enter Matrix B:\n");
            read(B, &r2, &c2);

            if(c1 == r2)
                product(A, B, r1, c1, c2);
            else
                printf("Multiplication not possible!\n");
        }
        else if(ch == 3) {
            printf("Enter Matrix:\n");
            read(A, &r1, &c1);
            transpose(A, r1, c1);
        }
        else if(ch != 4) {
            printf("Invalid choice!\n");
        }

    } while(ch != 4);

    return 0;
}