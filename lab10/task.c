#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct cone
{
   float R;
   float H;
};


void square_print(struct cone cone){
    float l = sqrt(pow(cone.R, 2) + pow(cone.H, 2));
    float V = (1.0/3.0) * 3.14 * pow(cone.R, 2) * cone.H;
    float Sp = 3.14 * cone.R * (cone.R + l);
    printf("Объем конуса: %f, Площадь поверхности: %f\n", 
        V, Sp);
}


struct cone* create_cone(int N) {
    struct cone* cones = (struct cone*)malloc(N * sizeof(struct cone));
    
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