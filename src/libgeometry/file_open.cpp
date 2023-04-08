#include "file_open.h"
FILE* file_open()
{
    FILE* fp;
    if ((fp = fopen("Input.txt", "r")) == NULL) {
        printf("\nInvalid to open file\n");
        return 0;
    }
    return fp;
}
