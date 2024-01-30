#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "eval.h"

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int redirect_to_file(struct ast *cmd_node)
{
    struct ast *redir_node = cmd_node->children[0];
    char **cmd = cmd_node->data;
    char ***argvs = malloc(sizeof(char **) * redir_node->nb_children);
    for (size_t i = 0; i < redir_node->nb_children; i++)
    {
        argvs[i] = redir_node->children[i]->data;
    }

    int fd = open(redir_node->data[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        error("open");
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        error("fork");
    }
    if (pid == 0)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            error("dup2");
        }
        close(fd);
        size_t size = 0;
        for (size = 0; cmd[size] != NULL; size++)
            ;
        if (cmd_handler(cmd, size) == 127)
        {
            return 127;
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            fprintf(stderr, "terminated by signal %d\n", WTERMSIG(status));
            return 1;
        }

        close(fd);
    }
    return 0;
}
int redirect_to_stdin(struct ast *cmd_node)
{}

int redirect_to_end_of_file(struct ast *cmd_node)
{
    struct ast *redir_node = cmd_node->children[0];
    char **cmd = cmd_node->data;
    char ***argvs = malloc(sizeof(char **) * redir_node->nb_children);
    for (size_t i = 0; i < redir_node->nb_children; i++)
    {
        argvs[i] = redir_node->children[i]->data;
    }
    int fd = open(redir_node->data[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        error("open");
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        error("fork");
    }

    if (pid == 0)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            error("dup2");
        }
        close(fd);
        size_t size = 0;
        for (size = 0; cmd[size] != NULL; size++)
            ;
        if (cmd_handler(cmd, size) == 127)
        {
            return 127;
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            fprintf(stderr, "terminated by signal %d\n", WTERMSIG(status));
            return 127;
        }
        close(fd);
    }
    return 0;
}

int redirect_to_fd(struct ast *cmd_node)
{
    struct ast *redir_node = cmd_node->children[0];
    char **cmd = cmd_node->data;
    char ***argvs = malloc(sizeof(char **) * redir_node->nb_children);
    for (size_t i = 0; i < redir_node->nb_children; i++)
    {
        argvs[i] = redir_node->children[i]->data;
    }
    int fd_out;
    int isCorrect = 1;
    size_t length = strlen(redir_node->data[1]);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(redir_node->data[1][i]))
        {
            isCorrect = 0;
        }
    }
    if (isCorrect)
    {
        fd_out = atoi(redir_node->data[1]);
    }
    else if (redir_node->data[1][0] == '-')
    {
        fd_out = -1;
    }
    int fd_in = open(redir_node->data[2], O_RDONLY);
    pid_t pid = fork();
    if (pid == 0)
    {
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            error("dup2");
        }
        close(fd_in);
        if (fd_out != -1)
        {
            if (dup2(fd_out, STDOUT_FILENO) == -1)
            {
                error("dup2");
            }
            close(fd_out);
        }
        size_t size = 0;
        for (size = 0; cmd[size] != NULL; size++)
            ;
        if (cmd_handler(cmd, size) == 127)
        {
            return 127;
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            return 127;
        }
        close(fd_in);
    }
    return 0;
}

int redirect_fd_to_fd(struct ast *cmd_node)
{}

int redirect_open_and_write(struct ast *cmd_node)
{
    int fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        error("open");
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        error("fork");
    }

    if (pid == 0)
    { // Child process
        // Redirect stdin from the file
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            error("dup2");
        }

        // Redirect stdout to the file
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            error("dup2");
        }

        // Close the original file descriptor
        close(fd);

        // Execute the command
        if (execvp(command, data + 2) == -1)
        {
            perror("execvp");
            exit(127);
        }
    }
    else
    { // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("%s exited with %d!\n", command, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            fprintf(stderr, "%s terminated by signal %d\n", command,
                    WTERMSIG(status));
            exit(1);
        }
    }
}

int select_pipe(struct ast *node, char **data)
{
    if (strcmp(data[1], ">") == 0)
    {
        return redirect_to_file(node);
    }
    if (strcmp(data[1], "<") == 0)
    {
        return redirect_to_stdin(node);
    }
    if (strcmp(data[1], ">>") == 0)
    {
        return redirect_to_end_of_file(node);
    }
    if (strcmp(data[1], ">&") == 0)
    {
        return redirect_to_fd(node);
    }
    if (strcmp(data[1], "<&") == 0)
    {
        return redirect_fd_to_fd(node);
    }
    if (strcmp(data[1], ">|") == 0)
    {
        return redirect_to_file(node);
    }
    if (strcmp(data[1], "<>") == 0)
    {
        return redirect_open_and_write(node);
    }
    return 127;
}