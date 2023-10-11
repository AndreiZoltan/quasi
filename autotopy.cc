#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h> 

#include "tools.hpp"
#include "autotopy.hpp"

int factorial(int n){
    if (n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

int perm(int *p, int x){
    int i = 0;
    while (p[i] != x){
        i++;
    }
    return i;
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


void init_perm(int *p){
    for (int i = 0; i < ROWS; i++) {
        p[i] = i;
    }
}



void find_autotopies(int *q, std::vector<int> &autotopy){
    int size = factorial(ROWS);
    std::vector<int> alpha(ROWS), beta(ROWS), gamma(ROWS);
    init_perm(&alpha[0]);
    init_perm(&beta[0]);
    init_perm(&gamma[0]);

    for (auto it = alpha.begin(); ; ) {
        for (auto it2 = beta.begin(); ; ) {
            for (auto it3 = gamma.begin(); ; ) {
                if (check_autotopy(q, &alpha[0], &beta[0], &gamma[0])){
                    autotopy.insert(autotopy.end(), alpha.begin(), alpha.end());
                    autotopy.insert(autotopy.end(), beta.begin(), beta.end());
                    autotopy.insert(autotopy.end(), gamma.begin(), gamma.end());
                    for (const auto& e : autotopy) {
                        std::cout << e;
                    }
                    std::cout << "\n";
                }
                if (!std::next_permutation(it3, gamma.end())) {
                    break;
                }
            }
            if (!std::next_permutation(it2, beta.end())) {
                break;
            }
        }
        if (!std::next_permutation(it, alpha.end())) {
        break;
        }
    }
}


int main(){
    int *qgroup = (int *)malloc(ROWS*COLS * sizeof(int));
    read_file(qgroup, "quasigroup.csv");
    std::cout << "Quasigroup: \n";
    print_matrix(qgroup);
    std::vector<int> autotopy;
    find_autotopies(qgroup, autotopy);
}