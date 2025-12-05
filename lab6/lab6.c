    #include <stdio.h>
    #include <stdlib.h>
    #define N 8

    float** create_matrix(int n){
        float** matrix = (float**)malloc(n * sizeof(float*));
        if(matrix == NULL) {
            return NULL;
        }
        for (int i = 0; i < n; i++){
            matrix[i] = (float*)malloc(n * sizeof(float));
        }
        return matrix;
    }      

    float** create_minor(float** sourse, int n, int line, int column){
        float** minor = create_matrix(n-1);
        int minor_i = 0;
        for (int  i = 0; i < n; i++){
            if (i == line) continue;

            int minor_j = 0;
            for (int j = 0; j < n; j++){
                if (j == column) continue;

                minor[minor_i][minor_j] = sourse[i][j];
                minor_j++;
            }
            minor_i++;
        }
        return minor;
    }

    float determinant(float** matrix, int n){
        if (n == 1) return matrix [0][0];
        if (n == 2) return matrix [0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        
        float det = 0;

        for (int j = 0; j < n; j++){
            float** minor = create_minor(matrix,n,0,j);
            float det_minor = determinant(minor, n - 1);

            if (j % 2 == 0){
                det += matrix[0][j] * det_minor;
            }
            else{
                det -= matrix[0][j] * det_minor;
            }
        
        }
        return det;
    }

    void replace_column(float** matrix, float* column, int n, int col_index) {
        for (int i = 0; i < n; i++) {
            matrix[i][col_index] = column[i];
        }
    }

    float** copy_matrix(float** source, int n) {
        float** copy = create_matrix(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                copy[i][j] = source[i][j];
            }
        }
        return copy;
    }

    void kramer(float** st, float* nd, float* otv, int n) {
        float main_det = determinant(st, n);
        
        if (main_det == 0) {
            printf("Система не имеет единственного решения!\n");
            return;
        }
        
        for (int el = 0; el < n; el++) {
            float** source_matrix = copy_matrix(st, n);
            
            replace_column(source_matrix, nd, n, el);
            
            float det_el = determinant(source_matrix, n);
            
            otv[el] = det_el / main_det;
        }
    }


    int main() {

        float st_values[N][N] = {
            { 2,   6,  -2,   3,  3,  6,   1,   6},
            { 1,   4,   4,   2,  4,  7,  -2,   3},
            { 3,   6,   7,  -1,  0,  5,   3,   1},
            { 7,   3,   6,   0,  7,  4,   2,   4},
            { 1,   0,  -1,   2,  3,  6,   0,  -2},
            {-1,   0,   2,   6, -2,  0,   5,  -1},
            { 4,   5,  -2,   7,  4,  4,   5,  -2},
            { 3,   3,   4,   6, -2,  6,  -2,   2}
        };
        float nd[] = {22, 39, 34, 23, 3, 26, 17, 37};
        
        float** st = create_matrix(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                st[i][j] = st_values[i][j];
            }
        }

        float otv[N];

        kramer(st, nd, otv, N);
        
        for (int i = 0; i < N; i++){
            printf("x%d = %.2f\n", i+1, otv[i]);
        }

        return 0;

    }
