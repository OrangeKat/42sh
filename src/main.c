#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stddef.h>

#include "lexer_parser/eval/eval.h"
#include "utils/file_to_string.h"
#include "lexer_parser/parser/parser.h"
#include "lexer_parser/lexer/lexer.h"
#include "lexer_parser/ast/ast.h"
#include "builtins/builtin.h"

int main(int argc,char **argv)
{
    FILE *f;
    //check if it there is a string argument
    if(strcmp("-c",argv[1]) == 0)
    {
        //create a file and copy argv[2] inside
        f = fmemopen(argv[2],strlen(argv[2]),"r");
    }
    // stdin
    else if(strcmp("<" ,argv[1]))
    {
        //cherck if file or not 
    }
    //if file 
    else
    {
        if((f = fopen(argv[1],"r")) == NULL)
        {
            err(-1,"not a file");
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
