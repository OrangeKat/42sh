#include "eval.h"

#include <string.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

static int run_piped_commands(struct ast *pipe_node)
{
    int num_commands = pipe_node->nb_children;
    char ***argvs = malloc(sizeof(char **) * pipe_node->nb_children);
    for (size_t i = 0; i < pipe_node->nb_children; i++)
    {
        argvs[i] = pipe_node->children[i]->data;
    }

    int **pipes = malloc(sizeof(int *) * (num_commands - 1));
    for (int i = 0; i < num_commands - 1; i++)
    {
        pipes[i] = malloc(sizeof(int) * 2);
    }

    for (int i = 0; i < num_commands - 1; ++i)
    {
        if (pipe(pipes[i]) == -1)
        {
            for (int i = 0; i < num_commands - 1; i++)
            {
                free(pipes[i]);
            }
            free(pipes);
            free(argvs);
            return 0;
        }
    }

    for (int i = 0; i < num_commands; ++i)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            for (int i = 0; i < num_commands - 1; i++)
            {
                free(pipes[i]);
            }
            free(pipes);
            free(argvs);
            return 0;
        }

        if (pid == 0)
        {
            if (i != 0)
            {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
                {
                    for (int i = 0; i < num_commands - 1; i++)
                    {
                        free(pipes[i]);
                    }
                    free(pipes);
                    free(argvs);
                    return 0;
                }
            }

            if (i != num_commands - 1)
            {
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
                {
                    for (int i = 0; i < num_commands - 1; i++)
                    {
                        free(pipes[i]);
                    }
                    free(pipes);
                    free(argvs);
                    return 0;
                }
            }

            for (int j = 0; j < num_commands - 1; ++j)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            size_t size = 0;
            for (size = 0; argvs[i][size] != NULL; size++);
            int ret = cmd_handler(argvs[i], size);
            for (int i = 0; i < num_commands - 1; i++)
            {
                free(pipes[i]);
            }
            free(pipes);
            free(argvs);
            return ret;
        }
    }

    for (int i = 0; i < num_commands - 1; ++i)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; ++i)
    {
        wait(NULL);
    }

    for (int i = 0; i < num_commands - 1; i++)
    {
        free(pipes[i]);
    }
    free(pipes);
    free(argvs);

    return 1;
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
            return run_piped_commands(ast);
        }
    }
    return 1;
}
