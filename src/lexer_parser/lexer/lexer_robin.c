#include "lexer_robin.h"

#include <err.h>
#include <stdlib.h>

#include "token_robin.h"
#include "../../utils/token_utils.h"

struct lexer *lexer_new(FILE *input_file)
{
    struct lexer *new = malloc(sizeof(struct lexer));
    new->input_file = input_file;
    new->current_tok = NULL;
    new->offset = 0;
    return new;
}

void lexer_free(struct lexer *lexer)
{
    if (lexer->current_tok)
    {
        free(lexer->current_tok);
    }
    free(lexer);
}

struct token *parse_input_for_tok(struct lexer *lexer)
{
    struct token *res = malloc(sizeof(struct token));
    size_t size = 1; 
    char *str = calloc(sizeof(char),size);
    char c;
    while((c = fgetc(lexer->input_file)) != EOF && !is_separator(c))
    {
        if(c == '\'')
        {
            res->value = get_string(lexer->input_file);
            res->type = TOKEN_WORD;
            return res;
        }
        if (c == '\n')
        {
            if(size == 1)
            {
                res->type = TOKEN_NL;
                return res;
            }
            str[size-1] = '\0';
            res->type = TOKEN_WORD;
            res->value = str;
            fseek(lexer->input_file,-1,SEEK_CUR);
            return res;
        }
        str[size-1] = c;
        size++;
        str = realloc(str,size);

    }
    str[size-1] = '\0'; 
    if (str[0] == '\0')
    {
        res->type = TOKEN_EOF;
        res->value = NULL;
        free(str);
    }
    res->type = TOKEN_WORD;
    res->value = str;
    return  res;
}

struct token *lexer_peek(struct lexer *lexer)
{
    if (lexer->current_tok == NULL)
    {
        lexer->current_tok = parse_input_for_tok(lexer);
    }
    return lexer->current_tok;
}

struct token *lexer_pop(struct lexer *lexer)
{
    struct token *to_pop = lexer_peek(lexer);
    lexer->current_tok = NULL;
    return to_pop;
}

/*int main(void)
{
    struct lexer *lex = lexer_new(fopen("test.sh","r"));
    struct token *tok = lexer_peek(lex);
    printf("%s\n",lex->current_tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("%s\n",lex->current_tok->value);
    tok = lexer_pop(lex);
    printf("%d\n",lexer_peek(lex)->type);
    return 0;
}*/