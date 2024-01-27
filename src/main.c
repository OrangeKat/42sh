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

int command_line_handler(FILE **f, char **argv, int argc, char **tmp)
{
    size_t length = 1;
    for (int i = 2; i < argc; i++)
    {
        length += strlen(argv[i]) + 1;
    }
    *tmp = malloc(length);
    *tmp[0] = '\0';
    for (int i = 2; i < argc; i++)
    {
        strcat(*tmp, argv[i]);
        if (i < argc - 1)
        {
            strcat(*tmp, " ");
        }
    }
    *f = fmemopen(*tmp, strlen(*tmp), "r");
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

int main(int argc, char **argv)
{
    FILE *f = NULL;
    size_t capacity = 64;
    char *buffer = malloc(capacity);
    char *tmp = NULL;
    // stdin
    if (argc == 1)
    {
        if (stdin_handler(&f, buffer, capacity) == 0)
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
        command_line_handler(&f, argv, argc, &tmp);
    }
    // read from a file
    else
    {
        file_handler(&f, argv);
    }

    if (f == NULL)
    {
        // error handling: not sure if necessary
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

    if (!ast_eval(tree_root))
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
    if (tmp)
    {
        free(tmp);
    }
    free(buffer);
    return 0;
}
