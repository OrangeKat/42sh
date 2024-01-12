#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_separator(char c)
{
    char separator_list[] = {' ','\n','\''};
    size_t size = 3;
    while(size > 0)
    {
        if (c == separator_list[size])
        {
            return 1;
        }
        size--;
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
    return res;
}
/*int main(void)
{
    FILE *fd;
    fd = fopen("test.sh","r");
    char c;
    char *s;
    while ((c = fgetc(fd))!= EOF)
    {
        if (c == '\'')
        {
            s = get_string(fd);
        }
    }
    printf("%s\n",s);
    return 0;
}*/