#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

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
enum parser_status parse(struct ast **res, struct lexer *lexer);

/*
    simple_command = WORD { element } ;
*/
enum parser_status parse_exp(struct ast **res, struct lexer *lexer);

/*
    element = WORD ;
*/
enum parser_status parse_sexp(struct ast **res, struct lexer *lexer);

#endif /* !PARSER_H */
