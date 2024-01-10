#include "lexer.h"

#include <stdlib.h>
#include <err.h>

void token_push(struct token_list *tokens, struct token *token)
{
    token->next = tokens->head;
    tokens->head = token;
    tokens->size++;
}

struct token *token_pop(struct token_list *tokens)
{
    struct token *res = tokens->head;
    tokens->head = res->next;
    res->next = NULL;
    tokens->size--;
    return res;
}

void token_free(struct token *token)
{
    //TODO
}

void token_list_destroy(struct token_list *tokens)
{
    //TODO
}

struct token_list *token_list_genesis(char *input)
{
    //TODO
    return NULL;
}
