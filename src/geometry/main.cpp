#include "compute.h"
#include "file_read.h"
#include "error_handler.h"
#include "get_args.h"

int main() {
    FILE* fp = file_open();
    int str_count = 0;
    char** list = file_read(fp, str_count);
    double** args = (double**)malloc(str_count * sizeof(double*));
    for (int i = 0; i < str_count; i++) {
        puts(list[i]);
        if (error_handler(list[i]) && get_args(list[i])) {
            args[i] = (double*)malloc(3 * sizeof(double));
            for (int j = 0; j < 3; j++)
                args[i][j] = get_args(list[i])[j];
            if (args[i][2] < 0) {
                printf("Radius cannot be negative!\n\n");
                continue;
            }
            else {
                printf(" perimeter = %g", perim(args[i]));
                printf("\n area = %g", area(args[i]));
            }
        }
        else args[i] = NULL;
        printf("\n\n");
    }
    free(args);
    return 0;
}





