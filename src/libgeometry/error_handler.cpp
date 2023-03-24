#include "error_handler.h"
int error_handler(char* str)
{
    int i = 0;
    int len = strlen("circle");
    if (str[len] == ')') { // check left bracket
        for (int j = 0; j < len; j++)
            printf(" ");
        printf("^\nError at column %d: expected '('\n", (int)len);
        return 0;
    }
    while (str[i] != '(') {
        if (i >= len) { // check name
            printf("^\nError at column 0: expected 'circle'\n");
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
            printf("^\nError at column %d: expected ')'\n", i);
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
            printf("^\nError at column %d: expected '<double>'\n", i);
            return 0;
        }
        i++;
    }
    i++;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\r') {
            for (int j = 0; j < i; j++)
                printf(" ");
            printf("^\nError at column %d: unexpected token\n", i);
            return 0;
        }
        i++;
    }
    return 1;
}