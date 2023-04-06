#include <ctest.h>
#include "file_open.h"

CTEST(arithmetic_suite, simple_sum){
    FILE* open = file_open();

    ASSERT_NOT_NULL(open);
}