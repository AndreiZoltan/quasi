#include <iostream>
#include "autotopy.hpp"

void read_file(int *qgroup, char const *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    int i = 0;
    int j = 0;
    while (fscanf(fp, "%d", &qgroup[i*COLS + j]) == 1) {
        j++;
        if (fgetc(fp) == '\n') {
            i++;
            j = 0;
        }
    }
    fclose(fp);
}

void print_perm(int *p, char const *name){
    printf("%s = ", name);
    for (int i=0; i<3; i++){
        printf("%d ", p[i]);
    }
    printf("||");
}

void print_matrix(int *matrix){
    for (int i=0; i<COLS; i++){
        for (int j=0; j<ROWS; j++){
            printf("%d ", matrix[i*COLS + j]);
        }
        printf("\n");
    }
}