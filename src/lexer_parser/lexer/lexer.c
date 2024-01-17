#include "lexer.h"

#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "../../utils/token_utils.h"

struct lexer *lexer_new(FILE *input_file)
{
    struct lexer *new = malloc(sizeof(struct lexer));
    new->input_file = input_file;
    new->current_tok = parse_input_for_tok(new);
    new->offset = ftell(input_file);
    new->separator = 0;
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
            lexer->separator = 1;   
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
        return res;
    }
    res->type = TOKEN_WORD;
    res->value = str;
    return  res;
}

struct token *lexer_peek(struct lexer *lexer)
{
    fseek(lexer->input_file,lexer->offset,SEEK_SET);
    struct token *tok = parse_input_for_tok(lexer);
    return tok;
}

struct token *lexer_pop(struct lexer *lexer)
{
    struct token *to_pop = lexer->current_tok;
    struct token *peek = lexer_peek(lexer);
    lexer->current_tok = peek;
    lexer->offset = ftell(lexer->input_file);
    if(lexer->separator)
    {
        lexer->offset--;
        lexer->separator = 0; 
    }
    return to_pop;
}

int main(void)
{
    struct lexer *lex = lexer_new(fopen("test.sh","r"));
    struct token *tok = lexer_peek(lex);
    printf("%s\n",lex->current_tok->value);
    tok = lexer_pop(lex);
    tok = lexer_peek(lex);
    printf("%s\n",lex->current_tok->value);
    tok = lexer_pop(lex);
    printf("%d\n",lex->current_tok->type);
    return 0;
}
