#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast.h"
#include "../lexer/lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_UNEXPECTED_TOKEN,
};

/*
    input =
    simple_command '\n'
    | simple_command EOF
    | '\n'
    | EOF
    ;
*/
enum parser_status parse(struct ast **tree_list, struct lexer *lexer, size_t curr_root);

/*
    simple_command = WORD { element } ;
*/
enum parser_status parse_simple_command(struct lexer *lexer, struct ast **node);

/*
    element = WORD ;
*/
enum parser_status parse_element(struct lexer *lexer, struct ast *node);

#endif /* !PARSER_H */
