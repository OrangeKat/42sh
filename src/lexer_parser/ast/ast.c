#include "ast.h"

#include <err.h>
#include <stdlib.h>

struct ast *ast_genesis(enum ast_type type)
{
    struct ast *new = malloc(sizeof(struct ast));
    new->type = type;
    new->nb_children = 0;
    new->children = NULL;
    new->data = calloc(1, sizeof(char));

    return new;
}

void add_child_to_parent(struct ast *parent, struct ast *child)
{
    parent->children = realloc(parent->children, parent->nb_children + 1);
    parent->children[parent->nb_children] = child;
    parent->nb_children++;
}

void ast_destroy(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        ast_destroy(ast->children[i]);
    }
    free(ast->children);

    if (ast->data)
    {
        free(ast->data);
    }

    free(ast);
}
