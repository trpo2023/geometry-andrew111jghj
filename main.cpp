#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* file_open();
char** file_read(FILE* fp, int& str_count);
void error_handler(char* str);

int main() {
    FILE* fp = file_open();
    int str_count = 0;
    char** list = file_read(fp, str_count);
    for (int i = 0; i < str_count; i++) {
        puts(list[i]);

        error_handler(list[i]);
        printf("\n\n");
    }
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

void error_handler(char* str) {
    char sym;
    int i = 0;
    int len = strlen("circle");
    if (str[len] == ')') {    //check left bracket
        for (int j = 0; j < len; j++)
            printf(" ");
        printf("^\nError at column %d: expected '('\n", (int)len);
        return;
    }
    while (str[i] != '(') {
        if (i >= len) {    //check name
            printf("^\nError at column 0: expected 'circle'\n");
            return;
        }
        i++;
    }
    i++;
    while (str[i] != ')') {
        if ((str[i] == '\0' || str[i] == '(') && (str[i - 1] == '(' || isdigit(str[i - 1]) || str[i - 1] == ' ')) {
            for (int j = 0; j < i; j++)
                printf(" ");
            printf("^\nError at column %d: expected ')'\n", i);
            return;
        }
        if ((!isdigit(str[i]) && str[i] != ' ' && str[i] != ',' && str[i] != '-' && str[i] != '.') || (str[i] == '-' && !isdigit(str[i + 1]))
            || (str[i] == '.' && (!isdigit(str[i + 1]) || !isdigit(str[i - 1]))) || (str[i] == ',' && (!isdigit(str[i - 1]) || isdigit(str[i + 1])))) {
            for (int j = 0; j < i; j++)
                printf(" ");
            printf("^\nError at column %d: expected '<double>'\n", i);
            return;
        }
        i++;
    }
    i++;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            for (int j = 0; j < i; j++)
                printf(" ");
            printf("^\nError at column %d: unexpected token\n", i);
            return;
        }
        i++;
    }
}