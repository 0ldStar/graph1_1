#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

void printMatrix(double **matrix, const int *SIZE) {
    for (int i = 0; i < *SIZE; ++i) {
        for (int j = 0; j < *SIZE; ++j) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double diagonalMultiplication(double **matrix, const int *SIZE) {
    double rez = 1;
    for (int i = 0; i < *SIZE; ++i) rez *= matrix[i][i];
    return rez;
}

int zeroesCheck(const double *range, const int *SIZE) {
    int count = 0, flag = 1;
    for (int i = 0; i < *SIZE; ++i)
        if (range[i] == 0 && flag) {
            count++;
        } else flag = 0;
    return count;
}

int power(int a, int b) {
    int rez = 1;
    for (int i = 0; i < b; ++i) rez *= a;
    return rez;
}

int sort(double **matrix, int *SIZE) {
    int i, j, count = 0;
    double *temp;
    for (i = 0; i < *SIZE - 1; i++)
        for (j = 0; j < *SIZE - i - 1; j++) {
            if (zeroesCheck(matrix[j], SIZE) > zeroesCheck(matrix[j + 1], SIZE)) {
                count++;
                temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    return power(-1, count);
}

double gaussianDeterminant(double **matrix, int *SIZE) {
    int size = *SIZE;
    double first, factor;
    while (size > 1) {
        if (matrix[*SIZE - size][*SIZE - size] == 0) return 0;
        printf("%f\n", matrix[*SIZE - size][*SIZE - size]);
        first = matrix[*SIZE - size][*SIZE - size];
        for (int i = *SIZE - size + 1; i < *SIZE; ++i) {
            factor = matrix[i][*SIZE - size] / first;
            for (int j = *SIZE - size; j < *SIZE; ++j) {
                matrix[i][j] -= matrix[*SIZE - size][j] * factor;
            }
        }
        size--;
    }
    printf("__________\n");
    //printMatrix(matrix, SIZE);
    return diagonalMultiplication(matrix, SIZE);
}

void init() {
    FILE *fp1, *fp2;
    if ((fp1 = fopen("read.txt", "r")) == NULL) {
        printf("Can't open file 'read.txt'\n");
        exit(-1);
    }
    if ((fp2 = fopen("write.txt", "w")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        exit(-1);
    }
    double **matrix;
    double determinant;
    int SIZE, sign;
    clock_t time_start, time_finish;
    while (fscanf(fp1, "%d", &SIZE) == 1) {
        matrix = (double **) malloc(SIZE * sizeof(double *));
        for (int i = 0; i < SIZE; ++i) {
            matrix[i] = (double *) malloc(SIZE * sizeof(double));
            for (int j = 0; j < SIZE; ++j) {
                fscanf(fp1, "%lf", &matrix[i][j]);
            }
        }
        time_start = clock();
        sign = sort(matrix, &SIZE);
        determinant = gaussianDeterminant(matrix, &SIZE) * (double) sign;
        time_finish = clock();
        fprintf(fp2, "%ld %f\n", time_finish - time_start, determinant);
        for (int i = 0; i < SIZE; ++i) free(matrix[i]);
        free(matrix);
        if (determinant > DBL_MAX) exit(-2);
    }
    fclose(fp1);
    fclose(fp2);
}

int main() {
    init();
    return 0;
}
