#include "compute.h"

FILE* file_open();
char** file_read(FILE* fp, int& str_count);
int error_handler(char* str);

double* get_args(char* str);

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

FILE* file_open() {

    FILE* fp;
    if ((fp = fopen("Input.txt", "r")) == NULL) {
        printf("\nInvalid to open file\n");
        return 0;
    }
    return fp;
}

char** file_read(FILE* fp, int& str_count) {

    char sym;
    int count = 1, str_num = 0;
    while (!feof(fp)) {
        sym = fgetc(fp);
        if (sym == '\n')
            count++;
    }
    str_count = count;
    rewind(fp);
    char** list = (char**)malloc(count * sizeof(char*));
    count = 0;
    while (!feof(fp)) {
        sym = fgetc(fp);
        if (sym == '\n' || sym == EOF)
            list[str_num++] = (char*)malloc(sizeof(char));
    }
    rewind(fp);
    str_num = 0;
    while (!feof(fp)) {
        sym = fgetc(fp);
        if (sym != ' ' || list[str_num][count - 1] != ' ') {
            count++;
            list[str_num] = (char*)realloc(list[str_num], count * sizeof(char));
            if (sym != EOF) {
                list[str_num][count - 1] = tolower(sym);
            }
            if (sym == '\n' || sym == EOF) {

                list[str_num][count - 1] = '\0';
                count = 0;
                str_num++;
            }
        }
    }
    fclose(fp);
    return list;
}

int error_handler(char* str) {
    int i = 0;
    int len = strlen("circle");
    if (str[len] == ')') {    //check left bracket
        for (int j = 0; j < len; j++)
            printf(" ");
        printf("^\nError at column %d: expected '('\n", (int)len);
        return 0;
    }
    while (str[i] != '(') {
        if (i >= len) {    //check name
            printf("^\nError at column 0: expected 'circle'\n");
            return 0;
        }
        i++;
    }
    i++;
    while (str[i] != ')') {
        if ((str[i] == '\0' || str[i] == '(' || str[i] == '\r') && (str[i - 1] == '(' || isdigit(str[i - 1]) || str[i - 1] == ' ')) {
            for (int j = 0; j < i; j++)
                printf(" ");
            printf("^\nError at column %d: expected ')'\n", i);
            return 0;
        }
        if ((!isdigit(str[i]) && str[i] != ' ' && str[i] != ',' && str[i] != '-' && str[i] != '.') || (str[i] == '-' && !isdigit(str[i + 1]))
            || (str[i] == '.' && (!isdigit(str[i + 1]) || !isdigit(str[i - 1]))) || (str[i] == ',' && (!isdigit(str[i - 1]) || isdigit(str[i + 1])))) {
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

double* get_args(char* str) {

    static double args[3] = { 0 };
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