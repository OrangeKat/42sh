#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

enum token_type
{
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_WORDS
};

struct token
{
    enum token_type type;
    char *value;
    struct token *next;
};

struct token_list
{
    struct token *head;
    size_t size;
};

void token_push(struct token_list *tokens, struct token *token);
struct token *token_pop(struct token_list *tokens);
void token_free(struct token *token);
void token_list_destroy(struct token_list *tokens);
struct token_list *token_list_genesis(char *input);

#endif // LEXER_H
