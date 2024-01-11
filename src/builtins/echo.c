#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"

//@params: str:char * the string where we want to extend two chars to the new
// char
//         index:size_t the index where we start
//         new:char the char that will take the place of the two chars at index
//         and index + 1
void extend_char(char *str, size_t index, char new)
{
    str[index++] = new;
    while (str[index] != '\0')
    {
        str[index] = str[index + 1];
        index++;
    }
}

//@params: str: char * the string in which we want to extend two chars to their
// special one
void extend_string(char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        if (str[i++] == '\\')
        {
            if (str[i] == 'n')
            {
                extend_char(str, i - 1, '\n');
            }
            else if (str[i] == 't')
            {
                extend_char(str, i - 1, '\t');
            }
            else if (str[i] == '\\')
            {
                extend_char(str, i - 1, '\\');
            }
        }
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
    if (extend)
    {
        extend_string(res);
    }
    printf("%s", res);
    if (newline)
    {
        putchar('\n');
    }
    free(res);
    return 0;
}
