#include "lexer.h"

#include <err.h>
#include <stdlib.h>
#include <string.h>

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
    free(token->value);
    free(token);
}

void token_list_destroy(struct token_list *tokens)
{
    struct token *curr = tokens->head;
    while (curr != NULL)
    {
        struct token *tmp = curr;
        token_free(curr);
        curr = tmp->next;
    }
}

int token_handler(struct token_list tokens, char *word)
{
    struct token *token = malloc(sizeof(struct token));
    token->value = NULL;
    if (strcmp(word, "if") == 0)
    {
        token->type = TOKEN_IF;
        token_push(tokens, token);
        return 3;
    }
    else if (strcmp(word, "then") == 0)
    {
        token->type = TOKEN_THEN;
        token_push(tokens, token);
        return -1;
    }
    else if (strcmp(word, "elif") == 0)
    {
        token->type = TOKEN_ELIF;
        token_push(tokens, token);
        return 2;
    }
    else if (strcmp(word, "else") == 0)
    {
        token->type = TOKEN_ELSE;
        token_push(tokens, token);
        return 0;
    }
    else if (strcmp(word, ";") == 0)
    {
        free(token);
        return -1;
    }
    else if (strcmp(word, "fi") == 0)
    {
        free(token);
        return -1;
    }
    else
    {
        token->type = TOKEN_WORDS;
        token_push(tokens, token);
        return 0;
    }
}



struct token_list *token_list_genesis(char *input)
{
    struct token_list *tokens = malloc(sizeof(struct token_list));
    int counter = 0;

}
