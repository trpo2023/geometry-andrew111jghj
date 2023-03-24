#include "get_args.h"
double* get_args(char* str)
{
    static double args[3] = {0};
    int i = strlen("circle"), num_count = 0, args_count = 0;
    char num[10] = "";
    while (str[i - 1] != ')') {
        if (isdigit(str[i]))
            num[num_count++] = str[i];
        else if (str[i] == '.' || str[i] == '-')
            num[num_count++] = str[i];
        else if (strcmp(num, "")) {
            if (args_count > 2) {
                printf("Error: too many arguments");
                return NULL;
            }
            num[num_count] = '\0';
            args[args_count++] = strtod(num, NULL);
            strcpy(num, "");
            num_count = 0;
        }

        i++;
    }
    if (args_count <= 2) {
        printf("Error: too low arguments");
        return NULL;
    }
    return args;
}