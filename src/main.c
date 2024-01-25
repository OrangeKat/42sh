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
        if (tmp_buff[0] == EOF || tmp_buff[0] == '\n')
        {
            break;
        }
        if (length + 1 > capacity)
        {
            capacity *= 2;
            char *tmp = realloc(buffer, capacity);
            if (!tmp)
            {
                free(buffer);
                return 2;
            }
            buffer = tmp;
        }
        buffer[length++] = tmp_buff[0];
    }
    buffer[++length] = '\0';
    *f = fmemopen(buffer, length - 1, "r");
    return 0;
}

int command_line_handler(FILE **f, int argc, char **argv, int i)
{
    // raise an error "use case: ./42sh -c [command]"
    if (argc <= 2)
    {
        return 2;
    }
    // create a file and copy argv[2] inside
    *f = fmemopen(argv[i], strlen(argv[i]), "r");
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
    // stdin
    if (argc == 1)
    {
        stdin_handler(&f, buffer, capacity);
    }
    // check if it there is a string argument
    else if (strcmp("-c", argv[1]) == 0)
    {
        int i;
        for (i = 2; i < argc; i++)
        {
             if (command_line_handler(&f, argc, argv, i) == 2)
             {
                err(2,"missing an argument");
             }
             if (strlen(argv[2]) == 0)
             {
             err(127, "expected a non empty argument");
             }
        }
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
    free(buffer);
    return 0;
}
