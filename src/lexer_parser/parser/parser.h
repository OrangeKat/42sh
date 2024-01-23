#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast.h"
#include "../lexer/lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_NOK,
};

/*
    input =
    simple_command '\n'
    | simple_command EOF
    | '\n'
    | EOF
    ;
*/
enum parser_status parse(struct ast **root, struct lexer *lexer);

/*
    list = simple_command { ; simple_command } [ ; ] ;
*/
static enum parser_status parse_pipeline(struct lexer *lexer, struct ast **node);

/*
    simple_command = WORD { element } ;
*/
//enum parser_status parse_simple_command(struct lexer *lexer, struct ast **node);

/*
    element = WORD ;
*/
//enum parser_status parse_element(struct lexer *lexer, struct ast *node);

//enum parser_status parse_if_else(struct lexer *lexer, struct ast **node);

#endif /* !PARSER_H */
