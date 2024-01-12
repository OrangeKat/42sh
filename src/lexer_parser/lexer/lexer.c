#include "lexer.h"

#include <err.h>
#include <stdlib.h>

#include "token.h"

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
    if (new->current_tok)
    {
        free(new->current_tok);
    }
    free(lexer);
}

struct token *parse_input_for_tok(struct lexer *lexer)
{
    FILE *fp = fopen(lexer->input_file, "r");
    fseek()
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
