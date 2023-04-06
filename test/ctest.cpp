#include <ctest.h>
#include "file_open.h"
#include "compute.h"
#include "intersect.h"

CTEST(ctest, not_null_pointer){
    FILE* open = file_open();
    ASSERT_NOT_NULL(open);
}

CTEST(ctest, perimeter) {
    double r[2];
    r[2] = 8.067;
    const double PI = 3.1415926535;
    double expected = 2 * PI * r[2];
    double result = perim(r);
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-1);
}

CTEST(ctest, area) {
    double r[2];
    r[2] = 8.067;
    const double PI = 3.1415926535;
    double expected = PI * r[2] * r[2];
    double result = area(r);
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-1);
}

CTEST(ctest, intersection) {
    double circ1[3]={0.8, 1.9, 2.3}, circ2[3]={105, 1.9, 2.5};
    double expected = 0;
    double result = intersect(circ1, circ2);
    ASSERT_EQUAL(expected, result);
}