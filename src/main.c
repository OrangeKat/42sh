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

int stdin_handler(FILE **f)
{
    char buffer[1024];
    if (read(STDIN_FILENO, buffer, 1024) < 0)
    {
        // error handling: could not read stdin
    }
    *f = fmemopen(buffer, strlen(buffer), "r");
    return 0;
}

int command_line_handler(FILE **f, int argc, char **argv)
{
    // raise an error "use case: ./42sh -c [command]"
    if (argc == 2)
    {
    }
    // create a file and copy argv[2] inside
    *f = fmemopen(argv[2], strlen(argv[2]), "r");
    return 0;
}

int file_handler(FILE **f, char **argv)
{
    if ((*f = fopen(argv[1], "r")) == NULL)
    {
        err(-1, "not a file");
    }
    // file
    else
    {
    }
    return 0;
}

int main(int argc, char **argv)
{
    FILE *f = NULL;
    // stdin
    if (argc == 1)
    {
        stdin_handler(&f);
    }
    // check if it there is a string argument
    else if (strcmp("-c", argv[1]) == 0)
    {
        command_line_handler(&f, argc, argv);
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
        lexer_destroy(lexer);
        ast_destroy(tree_root);
        return 1;
    }

    ast_eval(tree_root);

    ast_destroy(tree_root);
    lexer_destroy(lexer);
    fclose(f);
    return 0;
}
