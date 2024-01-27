#include "lexer.h"

#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/token_utils.h"
#include "token.h"

struct lexer *lexer_genesis(FILE *input_file)
{
    struct lexer *new = malloc(sizeof(struct lexer));
    new->input_file = input_file;
    new->separator = 0;
    new->current_tok = parse_input_for_tok(new);
    new->offset = ftell(input_file);
    if (new->separator)
    {
        new->offset--;
        new->separator = 0;
    }
    return new;
}

void lexer_destroy(struct lexer *lexer)
{
    if (lexer->current_tok)
    {
        if (lexer->current_tok->value)
        {
            free(lexer->current_tok->value);
        }
        free(lexer->current_tok);
    }
    free(lexer);
}

struct token *lexer_single_quote(struct lexer *lexer,char *str,struct token *res)
{
    free(str);
    res->value = get_string(lexer->input_file);
    res->type = TOKEN_WORD;
    return res;
}

struct token *lexer_double_quote(struct lexer *lexer,char *str,struct token *res)
{
    char c;
    free(str);
    res->type = TOKEN_VAR;
    if((c = fgetc(lexer->input_file)) != '$')
    {
            fseek(lexer->input_file, -1, SEEK_CUR);
        res->type = TOKEN_WORD;
    }
    res->value = get_double_quote(lexer->input_file);
    return res;
}
struct token *parse_input_for_tok(struct lexer *lexer)
{
    struct token *res = malloc(sizeof(struct token));
    res->value = NULL;
    size_t size = 1;
    char *str = calloc(sizeof(char), size);
    char c;
    while ((c = fgetc(lexer->input_file)) != EOF && is_separator(c))
    {
        continue;
    }
    if (c != EOF)
    {
        if (c == '#')
        {
            skip_comment(lexer);
        }
        else
        {
            fseek(lexer->input_file, -1, SEEK_CUR);
        }
    }
    while ((c = fgetc(lexer->input_file)) != EOF && !is_separator(c))
    {
        if (c == '\'')
        {
            /*free(str);
            res->value = get_string(lexer->input_file);
            res->type = TOKEN_WORD;
            return res;*/
            return lexer_single_quote(lexer,str,res);
        }
        if(c == '"')
        {
            /*free(str);
            res->type = TOKEN_VAR;
            if((c = fgetc(lexer->input_file)) != '$')
            {
                fseek(lexer->input_file, -1, SEEK_CUR);
                res->type = TOKEN_WORD;
            }
            res->value = get_double_quote(lexer->input_file);*/
            return lexer_double_quote(lexer,str,res);
        }
        if (c == '\n' || c == ';')
        {
            if (size == 1)
            {
                free(str);
                res->type = TOKEN_NL;
                return res;
            }
            str[size - 1] = '\0';
            res->type = TOKEN_WORD;
            res->value = str;
            lexer->separator = 1;
            return res;
        }
        str[size - 1] = c;
        size++;
        str = realloc(str, size);
    }
    str[size - 1] = '\0';
    return set_token(res, str);
}

struct token *lexer_peek(struct lexer *lexer)
{
    fseek(lexer->input_file, lexer->offset, SEEK_SET);
    struct token *tok = parse_input_for_tok(lexer);
    return tok;
}

struct token *lexer_pop(struct lexer *lexer)
{
    struct token *to_pop = lexer->current_tok;
    struct token *peek = lexer_peek(lexer);
    lexer->current_tok = peek;
    lexer->offset = ftell(lexer->input_file);
    if (lexer->separator)
    {
        lexer->offset--;
        lexer->separator = 0;
    }
    return to_pop;
}

/*
int main(void)
{
    struct lexer *lex = lexer_genesis(fopen("test.sh","r"));
    struct token *tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("current:%s\n",lex->current_tok->value);
    printf("peek:%s\n",tok->value);
    return 0;
}
*/
