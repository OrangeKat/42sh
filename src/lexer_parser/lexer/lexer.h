#ifndef LEXER_H
#define LEXER_H

#include "token.h"

struct lexer
{
    FILE *input_file; // The input data
    size_t offset; // The current offset inside the input data
    struct token *current_tok; // The next token, if processed
};

struct lexer *lexer_new(const char *input);

void lexer_free(struct lexer *lexer);

struct token *parse_input_for_tok(struct lexer *lexer);

struct token *lexer_peek(struct lexer *lexer);

struct token *lexer_pop(struct lexer *lexer);

#endif /* !LEXER_H */
