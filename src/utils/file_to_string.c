#include "file_to_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file_to_string(FILE *f)
{
    size_t size = 50;
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    char *res = calloc(sizeof(char),size);
    while((nread = getline(&line, &len,f)) != -1)
    {
        if (len > size - strlen(res))
        {
            size += len*2;
            res = realloc(res,size);
        }
        strcat(res,line);
    }
    free(line);
    return res;
}
