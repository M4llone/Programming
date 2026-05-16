#include "smarthome.h"


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
    print_struct(arr, N);
    printf("\n---------------------\n\n");
    long long start = mtime();
    SelectSort(compare_by_rating, arr, N);
    long long end = mtime();

    double time_ms = (end - start) / 1000.0;
    print_struct(arr, N);
    printf("Время сортировки: %.3f мс\n", time_ms);
}