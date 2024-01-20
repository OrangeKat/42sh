#include "token_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer_parser/lexer/token.h"

int is_separator(char c)
{
    char separator_list[] = {' '};
    size_t size = 1;
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

struct token *set_token(struct token *res,char *str)
{
    if (str[0] == '\0')
    {
        res->type = TOKEN_EOF;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"if") == 0)
    {
        res->type = TOKEN_IF;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"else") == 0)
    {
        res->type = TOKEN_ELSE;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"fi") == 0)
    {
        res->type = TOKEN_FI;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"fi") == 0)
    {
        res->type = TOKEN_FI;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"elif") == 0)
    {
        res->type = TOKEN_ELIF;
        res->value = NULL;
        free(str);
        return res;
    }
    if(strcmp(str,"then") == 0)
    {
        res->type = TOKEN_THEN;
        res->value = NULL;
        free(str);
        return res;
    }
    res->type = TOKEN_WORD;
    res->value = str;
    return res;
}

char *get_string(FILE *fd)
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
    res[size-1] = '\0';
    return res;
}
char *get_word(FILE *fd)
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
    struct token *tok = malloc(sizeof(struct token));
    tok->type = 0;
    tok->value = NULL;
    char *str = "if";
    tok = set_token(tok,str);
    printf("%d\n",tok->type);
}*/
