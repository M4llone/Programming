#include <stdio.h>
#include <stdlib.h>
#define N 5

int** new_matrix(int n){
    int** matrix = malloc(n * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++){
        matrix[i] = malloc(n * sizeof(int));
    }
    return matrix;
}    

void trans_matrix(int** matrix, int n){
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void found_zero(int** matrix, int n){
    int flag = 0;
    int zero_i = 0;
    int zero_j = 0;

    for (int i = 0; i < n && !flag; i++){
        for (int j = 0; j < n && !flag; j++){
            if (matrix[i][j] == 0){
                flag = 1;
                zero_i = i;
                zero_j = j;
            }
        }
    }

    if (zero_i == 0 && zero_j == n-1) {
        trans_matrix(matrix, n);
    }
    
    int zero_count = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (matrix[i][j] == 0){
                zero_count++;
            }
        }
    }

    if (zero_count > n){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (matrix[i][j] == 0){
                    matrix[i][j] = zero_count;
                }
            }
        }
    }
}

int main(){
    int n = N;
    
    int test_matrix[N][N] = {
        {1, 2, 3, 4, 0},
        {6, 7, 8, 9, 0},
        {11, 0, 13, 14, 15},
        {16, 17, 18, 19, 0},
        {0, 22, 23, 24, 25}
    };
    

    int** matrix = new_matrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matrix[i][j] = test_matrix[i][j];
        }
    }

    found_zero(matrix, n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}