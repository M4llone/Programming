#ifndef GAMES_H
#define GAMES_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define N 10000

struct game
{
    char name[128];
    char genre[128];
    int release;
    float rating;
};

void fill_struct(struct game dest[], struct game src[], int n);
void print_struct(struct game games[], int n);
int compare_by_rating(struct game a, struct game b);
void SelectSort(int (*callback)(struct game a, struct game b),struct game dest[], int n);
long long mtime(void);

#endif