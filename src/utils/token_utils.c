#include "token_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_separator(char c)
{
    char separator_list[] = {' ','\n','\''};
    size_t size = 3;
    while(size > 0)
    {
        size--;
        if (c == separator_list[size])
        {
            return 1;
        }
    }
    return 0;
}

char* get_string(FILE *fd)
{
    char c;
    size_t size = 1;
    char *res = calloc(sizeof(char),size);
    while((c = fgetc(fd)) != '\'' && c != EOF)
    {
        res[size-1] = c;
        size++;
        res = realloc(res,size);
    }
    if(c == EOF)
    {
        free(res);
        return NULL;
    }
    res[size] = '\0';
    return res;
}
char * get_word(FILE *fd)
{
    size_t size = 1;
    char c;
    char * res = calloc(sizeof(char),1);
    while((c = fgetc(fd))!= EOF && !is_separator(c))
    {
        res[size-1] = c;
        size++;
        res = realloc(res,size);
    }
    res[size] = '\0';
    return res;
}
/*int main(void)
{
    FILE *fd;
    fd = fopen("test.sh","r");
    char c;
    char *s;
    char *s2;
    s = get_word(fd);
    s2 = get_word(fd);
    printf("%s\n",s);
    printf("%s\n",s2);
    c = fgetc(fd);
    printf("%d\n",c);
    return 0;
}*/