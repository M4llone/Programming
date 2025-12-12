#include "conus.h"


void square_print(struct cone *cone){
    float l = sqrt(pow(cone->R, 2) + pow(cone->H, 2));
    float V = (1.0/3.0) * 3.14 * pow(cone->R, 2) * cone->H;
    float Sp = 3.14 * cone->R * (cone->R + l);
    printf("Объем конуса: %f, Площадь поверхности: %f\n", 
        V, Sp);
}


struct cone* create_cone(int N) {
    struct cone* cones = malloc(N * sizeof(struct cone));
    
    if (cones == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < N; i++){
        printf("Конус %d\n", i+1);
        printf("Введите радиус: \n");
        scanf("%f", &cones[i].R);
        printf("Введите высоту: \n");   
        scanf("%f", &cones[i].H);
    }
    

    return cones;
}