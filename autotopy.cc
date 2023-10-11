#include <stdio.h>
// #include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h> 

#define COLS 4
#define ROWS 4

int factorial(int n){
    if (n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

void read_file(int *qgroup, char *filename){
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


int check_autotopy(int *q, int *alpha, int *beta, int *gamma){
    for (int i=0; i<COLS; i ++){
        for (int j=0; j<ROWS; j ++) {
            if (q[i*COLS + j] != perm(gamma, q[perm(alpha, i)*COLS + perm(beta, j)])){
                return 0;
            }
        }
    }
    return 1;
}



void find_autotopy(int *q, std::vector<int>& autotopy){
    int size = 3*factorial(ROWS);
    autotopy.resize(size*size*size);
    while (std::next_permutation(autotopy.begin(), autotopy.end())){
        if (check_autotopy(q, &autotopy[0], &autotopy[0] + factorial(ROWS), &autotopy[0] + 2*factorial(ROWS))){
            print_perm(&autotopy[0], "alpha");
            print_perm(&autotopy[0] + factorial(ROWS), "beta");
            print_perm(&autotopy[0] + 2*factorial(ROWS), "gamma");
            printf("\n");
        }
    }
}


int main(){
    int *qgroup = (int *)malloc(ROWS*COLS * sizeof(int));
    read_file(qgroup, "quasigroup4.csv");
    std::vector<int> autotopy;
    find_autotopy(qgroup, autotopy);
}