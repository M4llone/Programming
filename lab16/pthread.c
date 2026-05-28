#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int arg;
} thread_data;

typedef struct {
    int start_row;
    int end_row;
    int size;
    int **a;
    int **b;
    int **c;
} matrix_data;

void multi_matrix(int **a, int **b, int **c, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void print_matrix(int **matrix, int N, char name) {
    printf("Матрица %c:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_pthread(void *args) {
    printf("thread %d OFF\n", *((int *)args));
}

void *Sleepsort(void *args) {
    thread_data *data = (thread_data *)args;
    sleep(data->arg);
    printf("%d ", data->arg);
    free(data);
    return 0;
}

void *matrix_routine(void *args) {
    matrix_data *data = (matrix_data *)args;
    int N = data->size;
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            data->c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                data->c[i][j] += data->a[i][k] * data->b[k][j];
            }
        }
    }
    
    return NULL;
}
int a = 0;
void *routine(void *args) {
    pthread_cleanup_push(print_pthread, args);
    
    for (int i = 0; i < 10; i++) {
       // pthread_mutex_lock(&mutex);
        a++;
        printf("thread %d: i=%d\n", *((int *)args), i + 1);
      //  pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    
    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./thread <размер матрицы> <количество потоков>\n");
        return 1;
    }
    
    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    
    int **a = (int **)malloc(N * sizeof(int *));
    int **b = (int **)malloc(N * sizeof(int *));
    int **c = (int **)malloc(N * sizeof(int *));
    
    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(N * sizeof(int));
        b[i] = (int *)malloc(N * sizeof(int));
        c[i] = (int *)malloc(N * sizeof(int));
    }
    
    pthread_t *tid = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    matrix_data *mdata = (matrix_data *)malloc(num_threads * sizeof(matrix_data));
    
    int rows_per_thread = N / num_threads;
    int remaining_rows = N % num_threads;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = 1;
            b[i][j] = 1;
        }
    }
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        mdata[i].start_row = current_row;
        mdata[i].end_row = current_row + rows_per_thread + (i < remaining_rows ? 1 : 0);
        mdata[i].size = N;
        mdata[i].a = a;
        mdata[i].b = b;
        mdata[i].c = c;
        pthread_create(&tid[i], NULL, matrix_routine, &mdata[i]);
        current_row = mdata[i].end_row;
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(tid[i], NULL);
    }
    
    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
    
    printf("%d,%d,%.2f\n", N, num_threads, elapsed);
    
    for (int i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
    free(tid);
    free(mdata);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}