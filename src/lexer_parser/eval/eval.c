#include "eval.h"

#include "../../builtins/builtin.h"

static cmd_handler(char **data, size_t size)
{
    if (strcmp(data[0], "true"))
    {
        return bin_true();
    }
    else if (strcmp(data[0], "false"))
    {
        return bin_false();
    }
    else if (strcmp(data[0], "echo"))
    {
        return !echo(data, size, 0, 1);
    }
    else
    {
        return 0;
    }
}

int ast_eval(struct ast *ast)
{
    if (ast->type == AST_CMD)
    {
        size_t size = 0;
        while (ast->data[size] != NULL)
        {
            size++;
        }
        return cmd_handler(ast->data, size);
    }
    else if (ast->type == AST_LIST)
    {
        int ret_val = 1;
        for (size_t i = 0; i < ast->nb_children; i++)
        {
            if (!ast_eval(ast->children[i]))
            {
                ret_val = 0;
            }
        }
        return ret_val;
    }
    else if (ast->type == AST_IF)
    {
        if (ast_eval(ast->children[0]))
        {
            return ast_eval(ast->children[1]);
        }
        else
        {
            return ast_eval(ast->children[2]);
        }
    }
}
