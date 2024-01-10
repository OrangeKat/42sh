#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

enum ast_type
{
    AST_CONDITION,
    AST_ACTION,
    AST_WORD
}

struct ast_node
{
    enum ast_type type;
    struct ast_node *sibling;
    struct ast_node *child;
    char *value;
}

struct ast_node *ast_genesis(struct token_list *list);
void ast_destroy(struct ast_node *root);

#endif // ! PARSER_H
