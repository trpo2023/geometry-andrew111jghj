#include "file_read.h"

char** file_read(FILE* fp, int& str_count)
{
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