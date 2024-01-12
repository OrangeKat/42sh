#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_UNEXPECTED_TOKEN,
};

enum parser_status parse(struct ast **res, struct lexer *lexer);

enum parser_status parse_exp(struct ast **res, struct lexer *lexer);

/**
 * \brief Parse texp expressions separated by * and /
 *
 * sexp =      texp  { ('*' | '/' ) texp } ;
 */
enum parser_status parse_sexp(struct ast **res, struct lexer *lexer);

/**
 * \brief Parse either a number, a - a number, or a parenthesized expression
 *
 * texp =      NUMBER
 *          |  '-' NUMBER
 *          |  '-' '(' exp ')'
 *          |  '(' exp ')'
 *          ;
 */
enum parser_status parse_texp(struct ast **res, struct lexer *lexer);

#endif /* !PARSER_H */
