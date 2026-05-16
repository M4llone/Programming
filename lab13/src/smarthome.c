#include "../include/smarthome.h"

long long mtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (long long)t.tv_sec * 1000000 + t.tv_usec;
}

void fill_struct(struct game dest[], struct game src[], int n) {
    for(int i = 0; i < n; i++) {
        int random = rand() % 7;    
        dest[i] = src[random];
    }
}


void print_struct(struct game games[], int n){
    if (n > 20) {
        for (int i = 0; i < 10; i++) {
            printf("Game[%d/%d]: Name: %s, genre: %s, release: %d, rating: %.1f\n", 
                i + 1, n, games[i].name, games[i].genre, games[i].release, games[i].rating);
        }   
    } else{
        for (int i = 0; i < n; i++) {
            printf("Game[%d/%d]: Name: %s, genre: %s, release: %d, rating: %.1f\n", 
                i + 1, n, games[i].name, games[i].genre, games[i].release, games[i].rating);
        }
    }
}


int compare_by_rating(struct game a, struct game b) {
    return a.rating > b.rating;
}

void SelectSort(int (*callback)(struct game, struct game), struct game dest[], int n){
    for (int i = 0; i < n - 1; i++){
        int min = i;
        for (int j = i + 1; j < n; j++){
            if (callback(dest[min], dest[j])){
                min = j;
            }
        }
        if (i != min){
            struct game temp = dest[i];
            dest[i] = dest[min];
            dest[min] = temp;
        }
    }
}
