#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins/builtin.h"
#include "lexer_parser/ast/ast.h"
#include "lexer_parser/eval/eval.h"
#include "lexer_parser/lexer/lexer.h"
#include "lexer_parser/parser/parser.h"
#include "utils/file_to_string.h"

int stdin_handler(FILE **f, char *buffer, size_t capacity)
{
    buffer = malloc(capacity);
    size_t length = 0;
    char tmp_buff[1];
    while (read(STDIN_FILENO, tmp_buff, 1) > 0)
    {
        if (length + 1 > capacity)
        {
            capacity *= 2;
            char *buf = realloc(buffer, capacity);
            if (!buf)
            {
                free(buffer);
                return 2;
            }
            buffer = buf;
        }
        buffer[length++] = tmp_buff[0];
    }
    buffer[++length] = '\0';
    *f = fmemopen(buffer, length - 1, "r");
    return --length;
}

int command_line_handler(FILE **f, char **argv, int argc, char **buffer)
{
    size_t length = 0;
    for (int i = 2; i < argc; i++)
    {
        length += strlen(argv[i]) + 1;
    }
    *buffer = malloc(length);
    *buffer[0] = '\0';
    for (int i = 2; i < argc; i++)
    {
        strcat(*buffer, argv[i]);
        if (i < argc - 1)
        {
            strcat(*buffer, " ");
        }
    }
    *f = fmemopen(*buffer, strlen(*buffer), "r");
    return 0;
}

int file_handler(FILE **f, char **argv)
{
    *f = fopen(argv[1], "r");
    // error
    if (*f == NULL)
    {
        err(-1, "not a file");
    }
    return 0;
}

static int file_allocator(FILE **f, int argc, char **argv, char **buffer)
{
    size_t capacity = 64;
    // stdin
    if (argc == 1)
    {
        if (stdin_handler(f, *buffer, capacity) == 0)
        {
            err(127, "expected a non empty input");
        }
    }
    // check if it there is a string argument
    else if (strcmp("-c", argv[1]) == 0)
    {
        int i;
        if (argc <= 2)
        {
            err(2, "missing an argument");
        }
        for (i = 2; i < argc; i++)
        {
            if (strlen(argv[2]) == 0)
            {
                err(127, "expected a non empty argument");
            }
        }
        command_line_handler(f, argv, argc, buffer);
    }
    // read from a file
    else
    {
        file_handler(f, argv);
    }
    if (f == NULL)
    {
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    FILE *f = NULL;
    char *buffer = NULL;
    if (!file_allocator(&f, argc, argv, &buffer))
    {
        return 2;
    }

    struct lexer *lexer = lexer_genesis(f);
    struct ast *tree_root = NULL;
    if (parse(&tree_root, lexer) != PARSER_OK)
    {
        if (lexer)
        {
            lexer_destroy(lexer);
        }
        if (tree_root)
        {
            ast_destroy(tree_root);
        }
        return 2;
    }

    int ret_val = ast_eval(tree_root);
    if (!ret_val)
    {
        lexer_destroy(lexer);
        return 1;
    }
    if (tree_root)
    {
        ast_destroy(tree_root);
    }
    lexer_destroy(lexer);
    fclose(f);
    if (buffer)
    {
        free(buffer);
    }
    if (ret_val != 127)
    {
        return 0;
    }
    return ret_val;
}