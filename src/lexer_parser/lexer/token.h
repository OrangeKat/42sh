#ifndef TOKEN_H
#define TOKEN_H

#include <unistd.h>

enum token_type
{
    TOKEN_WORD,
    TOKEN_EOF,
    TOKEN_NL,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_ELIF,
    TOKEN_THEN
};


struct token
{
    enum token_type type; // The kind of token
    char* value; // If the token is a word, its value
};
#endif /* !TOKEN_H */
