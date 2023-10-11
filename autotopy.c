#include <stdio.h>
#include <stdlib.h>

#define COLS 3

void print_perm(int *p, char *name){
    printf("%s = ", name);
    for (int i=0; i<3; i++){
        printf("%d ", p[i]);
    }
    printf("||");
}

int perm(int *p, int x){
    int i = 0;
    while (p[i] != x){
        i++;
    }
    return i;
}

int check_autotopy(int *q, int *alpha, int *beta, int *gamma){
    for (int i=0; i<3; i ++){
        for (int j=0; j<3; j ++) {
            if (q[i*COLS + j] != perm(gamma, q[perm(alpha, i)*COLS + perm(beta, j)])){
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    // read matrix from quasigoup.csv
    FILE *fp;
    int *qgroup = (int *)malloc(9 * sizeof(int));
    fp = fopen("quasigroup.csv", "r");
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
    int permutations[] = {0, 1, 2,
                        0, 2, 1,
                        1, 0, 2,
                        1, 2, 0,
                        2, 0, 1,
                        2, 1, 0};
    int *autotopy = (int *)calloc(3*6*6*6, sizeof(int));
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 6; k++){
                if (check_autotopy(qgroup, &permutations[i*3], &permutations[j*3], &permutations[k*3])){
                    printf("Autotopy found: ");
                    print_perm(&permutations[i*3], "alpha");
                    print_perm(&permutations[j*3], "beta");
                    print_perm(&permutations[k*3], "gamma");
                    printf("\n");
                }
            }
        }
    }
}