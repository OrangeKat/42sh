#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

#include <stdio.h>

#include "../lexer_parser/lexer/token.h"

int is_separator(char c);

char *get_string(FILE *fd);

char *get_word(FILE *fd);

struct token *set_token(struct token *res, char *str);

#endif /*TOKEN_UTILS_H*/
