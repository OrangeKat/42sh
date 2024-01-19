#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins/builtin.h"
#include "lexer_parser/ast/ast.h"
#include "lexer_parser/eval/eval.h"
#include "lexer_parser/lexer/lexer.h"
#include "lexer_parser/parser/parser.h"
#include "utils/file_to_string.h"

int main(int argc, char **argv)
{
    FILE *f = NULL;
    // stdin
    if (argc == 1)
    {
    }
    // check if it there is a string argument
    else if (strcmp("-c", argv[1]) == 0)
    {
        // raise an error "use case: ./42sh -c [command]"
        if (argc == 2)
        {
        }
        // create a file and copy argv[2] inside
        f = fmemopen(argv[2], strlen(argv[2]), "r");
    }
    else
    {
        if ((f = fopen(argv[1], "r")) == NULL)
        {
            err(-1, "not a file");
        }
        // file
        else
        {
        }
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
