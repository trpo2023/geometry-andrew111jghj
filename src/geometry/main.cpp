#include "compute.h"
#include "error_handler.h"
#include "file_open.h"
#include "file_read.h"
#include "get_args.h"
#include "intersect.h"

int main()
{
    FILE* fp = file_open();
    int str_count = 0;
    char** list = file_read(fp, str_count);
    double** args = (double**)malloc(str_count * sizeof(double*));
    int if_intersect;
    for (int j = 0; j < str_count; j++)
        if (error_handler(list[j], 0) == 1) {
            args[j] = (double*)malloc(3 * sizeof(double));
            if (args[j] != NULL)
                for (int k = 0; k < 3; k++)
                    args[j][k] = get_args(list[j])[k];
        } else
            args[j] = NULL;

    for (int i = 0; i < str_count; i++) {
        if (args[i] == NULL) {
            puts(list[i]);
            error_handler(list[i], 1);
            continue;
        }
        puts(list[i]);
        error_handler(list[i], 1);
        if (args[i][2] >= 0) {
            printf(" perimeter = %g", perim(args[i]));
            printf("\n area = %g", area(args[i]));
            if_intersect = 1;
            for (int j = 0; j < str_count; j++)
                if (j != i && args[i] != NULL && args[j] != NULL
                    && intersect(args[j], args[i])) {
                    if (if_intersect) {
                        printf("\n intersects:");
                        if_intersect = 0;
                    }
                    printf("\n  %d. circle\n", j);
                }
        } else {
            printf("Radius cannot be negative!\n\n");
            continue;
        }
        printf("\n\n");
    }
    free(args);
    return 0;
}