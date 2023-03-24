#include "compute.h"

double perim(double* args) {
    const double PI = 3.1415926535;
    return 2 * PI * args[2];
}

double area(double* args) {
    const double PI = 3.1415926535;
    return PI * args[2] * args[2];
}