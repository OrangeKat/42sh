#include "eval.h"

#include <string.h>

#include "../../builtins/builtin.h"

static int cmd_handler(char **data, size_t size)
{
    if (strcmp(data[0], "true") == 0)
    {
        return bin_true();
    }
    else if (strcmp(data[0], "false") == 0)
    {
        return bin_false();
    }
    else if (strcmp(data[0], "echo") == 0)
    {
        return !echo(data, size);
    }
    else
    {
        return execvp(data[0], data);
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
            if (ast->nb_children == 3)
            {
                return ast_eval(ast->children[2]);
            }
            return 1;
        }
    }
    else if (ast->type == AST_PIPE)
    {
        if (ast->nb_children == 1)
        {
            return ast_eval(ast->children[0]);
        }
        else
        {
            //TODO
            return 123;
        }
    }
    return 1;
}
