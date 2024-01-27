#include "eval.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../builtins/builtin.h"

int cmd_handler(char **data, size_t size)
{
    if (strcmp(data[0], "true") == 0)
    {
        int res = bin_true();
        fflush(stdout);
        return res;
    }
    else if (strcmp(data[0], "false") == 0)
    {
        int res = bin_false();
        fflush(stdout);
        return res;
    }
    else if (strcmp(data[0], "echo") == 0)
    {
        int res = !echo(data, size);
        fflush(stdout);
        return res;
    }
    else
    {
        return execvp(data[0], data);
    }
}

static int ast_eval_cmd(struct ast *ast)
{
    size_t size = 0;
    while (ast->data[size] != NULL)
    {
        size++;
    }
    return cmd_handler(ast->data, size);
}

static int ast_eval_list(struct ast *ast)
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

static int ast_eval_if(struct ast *ast)
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

static int ast_eval_pipe(struct ast *ast)
{
    if (ast->nb_children == 1)
    {
        return ast_eval(ast->children[0]);
    }
    else
    {
        return run_piped_commands(ast);
    }
}

static int ast_eval_not(struct ast *ast)
{
    return !ast_eval(ast->children[0]);
}

static int ast_eval_while(struct ast *ast)
{
    int ret = 1;
    while (ast_eval(ast->children[0]))
    {
        ret = ast_eval(ast->children[1]);
    }
    return ret;
}

static int ast_eval_until(struct ast *ast)
{
    int ret = 1;
    while (!ast_eval(ast->children[0]))
    {
        ret = ast_eval(ast->children[1]);
    }
    return ret;
}

static int ast_eval_and(struct ast *ast)
{
    int ret;
    if ((ret = ast_eval(ast->children[0])))
    {
        return ast_eval(ast->children[1]);
    }
    return ret;
}

static int ast_eval_or(struct ast *ast)
{
    int ret;
    if (!(ret = ast_eval(ast->children[0])))
    {
        ret = ast_eval(ast->children[1]);
    }
    return ret;
}

int ast_eval(struct ast *ast)
{
    switch (ast->type)
    {
    case AST_CMD:
        return ast_eval_cmd(ast);
    case AST_LIST:
        return ast_eval_list(ast);
    case AST_IF:
        return ast_eval_if(ast);
    case AST_PIPE:
        return ast_eval_pipe(ast);
    case AST_NOT:
        return ast_eval_not(ast);
    case AST_WHILE:
        return ast_eval_while(ast);
    case AST_UNTIL:
        return ast_eval_until(ast);
    case AST_AND:
        return ast_eval_and(ast);
    case AST_OR:
        return ast_eval_or(ast);
    default:
        return 1;
    }
}
