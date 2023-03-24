#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
FILE* file_open();
char** file_read(FILE* fp, int& str_count);