#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
    int row;
    int col;
    int value;
} element;

void transpose(element a[], element b[]);

int main(void) {
    int num_rows, num_cols, num_terms, i;

    printf("enter the size of rows and columns. the number of non-zero terms : ");
    scanf("%d %d %d", &num_rows, &num_cols, &num_terms);

    element* a = (element*)malloc((num_terms + 1) * sizeof(element));
    element* b = (element*)malloc((num_terms + 1) * sizeof(element));

    a[0].row = num_rows;
    a[0].col = num_cols;
    a[0].value = num_terms;

    printf("enter row, column, and value pairs in order :\n");
    for (i = 1; i <= num_terms; i++) {
        scanf("%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    }

    transpose(a, b);

    printf("the transposed matrix is :\n");
    printf("row\tcol\tvalue\n");
    for (i = 1; i <= num_terms; i++) {
        printf("%d\t%d\t%d\n", b[i].row, b[i].col, b[i].value);
    }

    free(a);
    free(b);

    return 0;
}

void transpose(element a[], element b[]) {
    if (a[0].col == 0) {
        return;
    }
    int* row_terms = (int*)malloc((a[0].col + 1) * sizeof(int));
    int* starting_pos = (int*)malloc((a[0].col + 1) * sizeof(int));
    int i, j, num_cols = a[0].col, num_terms = a[0].value;

    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        for (i = 0; i < num_cols; i++) {
            row_terms[i] = 0;
        }

        for (i = 1; i <= num_terms; i++) {
            row_terms[a[i].col]++;
        }

        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++) {
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
        }

        for (i = 1; i <= num_terms; i++) {
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }

    free(row_terms);
    free(starting_pos);
}
