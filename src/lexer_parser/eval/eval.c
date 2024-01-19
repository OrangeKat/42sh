#include "eval.h"

#include "../../builtins/builtin.h"

void ast_eval(struct ast *ast)
{
    if (ast->type == AST_CMD)
    {
        int size = 0;
        while (ast->data[size] != NULL)
        {
            size++;
        }
        echo(ast->data, size, 0, 1);
    }
    else if (ast->type == AST_LIST)
    {
        for (int i = 0; i < ast->nb_children; i++)
        {
            ast_eval(ast->children[i]);
        }
    }
}
