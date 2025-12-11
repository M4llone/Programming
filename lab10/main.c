#include "conus.h"

int main(){
    int N;
    struct cone* cones;
    
    printf("Введите количество конусов: ");
    scanf("%d", &N);
    
    cones = create_cone(N);
    
    for (int i = 0; i < N; i++) {
        printf("Конус %d: ", i+1);
        square_print(cones[i]);
    }
}