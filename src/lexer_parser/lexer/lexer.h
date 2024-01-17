#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdio.h>

struct lexer
{
    FILE *input_file; // The input data
    size_t offset;// The current offset inside the input data
    struct token *current_tok; // The next token, if processed
    int separator;
};

struct lexer *lexer_new(FILE *input_file);

void lexer_free(struct lexer *lexer);

struct token *parse_input_for_tok(struct lexer *lexer);

struct token *lexer_peek(struct lexer *lexer);

struct token *lexer_pop(struct lexer *lexer);

#endif /* !LEXER_H */
