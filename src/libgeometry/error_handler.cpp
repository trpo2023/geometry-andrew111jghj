#include "error_handler.h"
int error_handler(char* str, int out_flag)
{
    int i = 0;
    int len = strlen("circle");
    if (str[len] == ')') { // check left bracket
        for (int j = 0; j < len; j++)
            printf(" ");

        if (out_flag)
            printf("^\nError at column %d: expected '('\n", (int)len);
        else
            printf("\n");
        return 0;
    }
    while (str[i] != '(') {
        if (i >= len) { // check name

            if (out_flag)
                printf("^\nError at column 0: expected 'circle'\n");
            else
                printf("\n");
            return 0;
        }
        i++;
    }
    i++;
    while (str[i] != ')') {
        if ((str[i] == '\0' || str[i] == '(' || str[i] == '\r')
            && (str[i - 1] == '(' || isdigit(str[i - 1])
                || str[i - 1] == ' ')) {
            for (int j = 0; j < i; j++)
                printf(" ");

            if (out_flag)
                printf("^\nError at column %d: expected ')'\n", i);
            else
                printf("\n");
            return 0;
        }
        if ((!isdigit(str[i]) && str[i] != ' ' && str[i] != ',' && str[i] != '-'
             && str[i] != '.')
            || (str[i] == '-' && !isdigit(str[i + 1]))
            || (str[i] == '.' && (!isdigit(str[i + 1]) || !isdigit(str[i - 1])))
            || (str[i] == ','
                && (!isdigit(str[i - 1]) || isdigit(str[i + 1])))) {
            for (int j = 0; j < i; j++)
                printf(" ");

            if (out_flag)
                printf("^\nError at column %d: expected '<double>'\n", i);
            else
                printf("\n");
            return 0;
        }
        i++;
    }
    i++;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\r') {
            for (int j = 0; j < i; j++)
                printf(" ");

            if (out_flag)
                printf("^\nError at column %d: unexpected token\n", i);
            else
                printf("\n");
            return 0;
        }
        i++;
    }
    return 1;
}