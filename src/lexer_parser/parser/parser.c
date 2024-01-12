#include "parser.h"

#include <stdlib.h>

#include "../lexer/lexer.h"

/*
    input =
    simple_command '\n'
    | simple_command EOF
    | '\n'
    | EOF
    ;
*/
enum parser_status parse(struct ast **res, struct lexer *lexer)
{
    if (lexer->current_tok->type == TOKEN_NL)
    {
        lexer_pop(lexer);
        return PARSER_OK;
    }
    else if (lexer->current_tok->type == TOKEN_EOF)
    {
        lexer_pop(lexer);
        return PARSER_OK;
    }
    else if (parse_simple_command == 1 && lexer_peek(lexer)->type == TOKEN_NL)
    {
        lexer_pop(lexer);
        lexer_pop(lexer);
        return PARSER_OK;
    }
    else if (parse_simple_command == 1 && lexer_peek(lexer)->type == TOKEN_EOF)
    {
        lexer_pop(lexer);
        lexer_pop(lexer);
        return PARSER_OK;
    }
    else 
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}

/*
    simple_command = WORD { element } ;
*/
enum parser_status parse_simple_command(struct ast **res, struct lexer *lexer)
{
    if (lexer->current_tok == TOKEN_WORD && parse_element(res, lexer) == PARSER_OK)
    {
        return PARSER_OK;
    }
    else
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}

                            /!\ WHEN POP ADD TO AST /!\

/*
    element = WORD ;
*/
enum parser_status parse_element(struct ast **res, struct lexer *lexer)
{
    if (lexer->current_tok->type == TOKEN_WORD)
    {
        lexer_pop(lexer);
        while (lexer_peek(lexer)->type == TOKEN_WORD)
        {
            lexer_pop(lexer);
        }
        return PARSER_OK;
    }
    else
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}
