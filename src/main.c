#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stddef.h>

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
    struct ast **tree_list = malloc(sizeof(struct ast *));
    if (parse(tree_list, lexer, 0) != PARSER_OK)
    {
        lexer_destroy(lexer);
        for (size_t i = 0; i < sizeof(tree_list) / sizeof(struct ast *); i++)
        {
            ast_destroy(tree_list[i]);
        }
        return 1;
    }

    for (size_t i = 0; i < sizeof(tree_list) / sizeof(struct ast *); i++)
    {
        int size = 0;
        while (tree_list[i]->data[size] != NULL){
            size++;
    }
        echo(tree_list[i]->data, size, 0, 1);
        ast_destroy(tree_list[i]);
    }
    free(tree_list);
    lexer_destroy(lexer);
    fclose(f);
    return 0;
}
