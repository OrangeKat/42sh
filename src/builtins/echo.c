#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"

//@params: str:char * the string which contains the character to escape
//         index:size_t the index where we escape the character
void escape_char(char *str, size_t index)
{
    char c;
    if (str[index] == '\n')
        c = 'n';
    else if (str[index] == '\t')
        c = 't';
    else
        c = '\0';
    // this should not happen and is a debug case
    str[index++] = '\\';
    char temp1 = str[index];
    char temp2;
    str[index++] = c;
    while (str[index - 1] != '\0')
    {
        temp2 = str[index];
        str[index++] = temp1;
        temp1 = temp2;
    }
}

//@params: str:char * the string to print
//         extend:int controls if \t are extended to tabs and \n to newline
//         0 by default if -e is not specified
//         newline:int controls if a newline is added at end of string
//         1 by default if -n is not specified
int echo(char *str, int extend, int newline)
{
    size_t len = strlen(str);
    char *res = malloc(sizeof(char) * (len + 1));
    if (res == NULL)
        return 1;
    strncpy(res, str, len);
    if (!extend)
    {
        size_t i = 0;
        while (res[i] != '\0')
        {
            if (res[i] == '\n' || res[i] == '\t')
            {
                len++;
            }
            i++;
        }
        res = realloc(res, len + 1);
        i = 0;
        while (res[i] != '\0')
        {
            if (res[i] == '\n' || res[i] == '\t')
            {
                escape_char(res, i);
            }
            i++;
        }
    }
    printf("%s", res);
    if (newline)
        putchar('\n');
    free(res);
    return 0;
}
