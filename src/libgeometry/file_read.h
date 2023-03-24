#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
FILE* file_open();
char** file_read(FILE* fp, int& str_count);