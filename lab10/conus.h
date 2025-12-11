#ifndef CONUS_H
#define CONUS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct cone
{
   float R;
   float H;
};


void square_print(struct cone cone);
struct cone* create_cone(int N);


#endif