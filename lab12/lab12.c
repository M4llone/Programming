#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 7

struct game
{
    char name[128];
    char genre[128];
    int release;
    float rating;
};

void fill_struct(struct game dest[], struct game src[], int n) {
    int random = rand() % n;
    for(int i = 0; i < n; i++) {
        int random = rand() % n;    
        strcpy(dest[i].name, src[random].name);
        strcpy(dest[i].genre, src[random].genre);
        dest[i].release = src[random].release;
        dest[i].rating = src[random].rating;
    }
}


void print_struct(struct game games[], int n){
    for (int i = 0; i < n; i++) {
        printf("Game[%d/%d]: Name: %s, genre: %s, release: %d, rating: %.1f\n", 
            i + 1, n, games[i].name, games[i].genre, games[i].release, games[i].rating);
    }   
}

void SelectSort(struct game dest[], int n){
    int temp;
    for (int i = 0; i < n - 1; i++){
        int min = i;
        for (int j = i + 1; j < n; j++){
            if (dest[j].rating > dest[min].rating){
                min = j;
            }
        }
        if (i != min){
            temp = dest[i].rating;
            dest[i].rating = dest[min].rating;
            dest[min].rating = temp;
        }
    }
}

int main (){
    srand(time(NULL));

    struct game games[] = {{"DOTA2", "MOBA", 2014, 8.9},
                          {"CS GO", "SHOOTER", 2000, 7.8},
                          {"MINECRAFT", "SANDBOX", 2011, 10},
                          {"ROBLOX", "PLATFORM", 2006, 6.7},
                          {"VALORANT", "SHOOTER", 2020, 9.1},
                          {"GENSHIN", "RPG", 2021, 9.9},
                          {"TERRARIA", "SANDBOX", 2001, 5.2}};
    struct game arr[N];
    fill_struct(arr, games, N);
    print_struct(arr,sizeof(games)/sizeof(games[0]));
    printf("\n---------------------\n\n");
    SelectSort(arr, N);
    print_struct(arr,sizeof(games)/sizeof(games[0]));
}