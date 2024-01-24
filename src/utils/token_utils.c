#include "token_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer_parser/lexer/lexer.h"
#include "../lexer_parser/lexer/token.h"

int is_separator(char c)
{
    char separator_list[] = { ' ' };
    size_t size = 1;
    while (size > 0)
    {
        size--;
        if (c == separator_list[size])
        {
            return 1;
        }
    }
    return 0;
}

int is_redir(char *str)
{
    if (strcmp(str, "<") == 0 || strcmp(str, ">") == 0)
    {
        return 1;
    }
    if (strcmp(str, ">>") == 0 || strcmp(str, ">&") == 0)
    {
        return 1;
    }
    if (strcmp(str, "<&") == 0 || strcmp(str, ">|") == 0)
    {
        return 1;
    }
    if (strcmp(str, "<>") == 0)
    {
        return 1;
    }
    return 0;
}

int set_token_loop(struct token *res, char *str)
{
    if (strcmp(str, "while") == 0)
    {
        res->type = TOKEN_WHILE;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "for") == 0)
    {
        res->type = TOKEN_FOR;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "until") == 0)
    {
        res->type = TOKEN_UNTIL;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "do") == 0)
    {
        res->type = TOKEN_DO;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "done") == 0)
    {
        res->type = TOKEN_DONE;
        res->value = NULL;
        free(str);
        return 1;
    }
    return 0;
}

int set_token_if(struct token *res, char *str)
{
    if (strcmp(str, "if") == 0)
    {
        res->type = TOKEN_IF;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "else") == 0)
    {
        res->type = TOKEN_ELSE;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "fi") == 0)
    {
        res->type = TOKEN_FI;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "fi") == 0)
    {
        res->type = TOKEN_FI;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "elif") == 0)
    {
        res->type = TOKEN_ELIF;
        res->value = NULL;
        free(str);
        return 1;
    }
    if (strcmp(str, "then") == 0)
    {
        res->type = TOKEN_THEN;
        res->value = NULL;
        free(str);
        return 1;
    }
    return 0;
}

struct token *set_token(struct token *res, char *str)
{
    if (str[0] == '\0')
    {
        res->type = TOKEN_EOF;
        res->value = NULL;
        free(str);
        return res;
    }
    if (set_token_if(res, str))
    {
        return res;
    }
    if (is_redir(str))
    {
        res->type = TOKEN_REDIR;
        res->value = str;
        return res;
    }
    if (strcmp(str, "!") == 0)
    {
        res->type = TOKEN_NOT;
        res->value = NULL;
        free(str);
        return res;
    }
    if (strcmp(str, "|") == 0)
    {
        res->type = TOKEN_PIPE;
        res->value = NULL;
        free(str);
        return res;
    }
    if (set_token_loop(res, str))
    {
        return res;
    }
    res->type = TOKEN_WORD;
    res->value = str;
    return res;
}

void skip_comment(struct lexer *lexer)
{
    char c;
    while ((c = fgetc(lexer->input_file)) != EOF && c != '\n')
    {
        continue;
    }
    if (c != EOF)
    {
        fseek(lexer->input_file, -1, SEEK_CUR);
    }
}
char *get_string(FILE *fd)
{
    char c;
    size_t size = 1;
    char *res = calloc(sizeof(char), size);
    while ((c = fgetc(fd)) != '\'' && c != EOF)
    {
        res[size - 1] = c;
        size++;
        res = realloc(res, size);
    }
    if (c == EOF)
    {
        free(res);
        return NULL;
    }
    res[size - 1] = '\0';
    return res;
}
char *get_word(FILE *fd)
{
    size_t size = 1;
    char c;
    char *res = calloc(sizeof(char), 1);
    while ((c = fgetc(fd)) != EOF && !is_separator(c))
    {
        res[size - 1] = c;
        size++;
        res = realloc(res, size);
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
