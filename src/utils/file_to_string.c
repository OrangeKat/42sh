#include "file_to_string.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file_to_string(FILE *f)
{
    size_t size = 50;
    char buffer[50];
    size_t nread;
    char *res = calloc(sizeof(char), size);
    while ((nread = fread(buffer, 1, 50, f)) != 0)
    {
        if (res[0] != '\0')
        {
            size += 100;
            res = realloc(res, size);
        }
        strcat(res, buffer);
    }
    res[size] = '\0';
    return res;
}
