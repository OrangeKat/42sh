#include "ast.h"

#include <err.h>
#include <stdlib.h>

struct ast *ast_genesis(enum ast_type type)
{
    struct ast *new = malloc(sizeof(struct ast));
    new->type = type;
    new->nbchildren = 0;
    new->children = NULL;
    new->data = calloc(1, sizeof(char));

    return new;
}

goid add_child_to_parent(struct ast *parent, struct ast *child)
{
    parent->children = realloc(parent->children, parent->nbchildren + 1);
    parent->children[parent->nb_children] = child;
    parent-nbchildren++;
}

void ast_destroy(struct ast *ast)
{
    for (size_t i = 0; i < ast->nbchildren; i++)
    {
        ast_free(ast->children[i]);
    }
    free(ast->children);

    if (ast->data)
    {
        free(ast->data);
    }

    free(ast);
}
