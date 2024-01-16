#ifndef AST_H
#define AST_H

#include <unistd.h>

enum ast_type
{
    AST_CMD,
    AST_IF,
    AST_LIST
};

struct ast
{
    enum ast_type type; // type of the node
    size_t nb_children; // size of children
    struct ast **children; // array of children
    void *data; // data contained in the node
};

#endif /* !AST_H */
