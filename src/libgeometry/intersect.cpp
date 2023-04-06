#include "intersect.h"

int intersect(double* args1, double* args2)
{
    if (sqrt(powf(abs(args1[0] - args2[0]), 2)
             + powf(abs(args1[1] - args2[1]), 2))
        < args1[2] + args2[2]) {
        return 1;
    }
    return 0;
}