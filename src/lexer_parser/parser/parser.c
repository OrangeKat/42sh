#include "parser.h"

#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

static char** add_to_data(char **data, char *word)
{
    size_t length = 0;
    while (data[length] != NULL)
    {
        length++;
    }
    data[length] = word;
    length++;

    data = realloc(data, (length + 1) * sizeof(char *));
    data[length] = NULL;
    return data;
}

/*
    input =
    simple_command '\n'
    | simple_command EOF
    | '\n'
    | EOF
    ;
*/
enum parser_status parse(struct ast **root, struct lexer *lexer)
{
    struct ast *ast_node = NULL;

    if (lexer->current_tok->type == TOKEN_NL)
    {
        free(lexer_pop(lexer));
        parse(root, lexer);
        return PARSER_OK;
    }
    else if (lexer->current_tok->type == TOKEN_EOF)
    {
        free(lexer_pop(lexer));
        return PARSER_OK;
    }
    else if (parse_list(lexer, &ast_node) == PARSER_OK)
    {
        *root = ast_node;
        parse(root, lexer);
        return PARSER_OK;
    }
    else 
    {
        lexer_destroy(lexer);
        return PARSER_UNEXPECTED_TOKEN;
    }
}

/*
    list = simple_command { ; simple_command } [ ; ] ;
*/
enum parser_status parse_list(struct lexer *lexer, struct ast **node)
{
    struct ast *new_list = ast_genesis(AST_LIST);
    *node = new_list;
    while (lexer->current_tok->type != TOKEN_EOF)
    {
        struct ast *ast_node = NULL;
        if (parse_simple_command(lexer, &ast_node) == PARSER_UNEXPECTED_TOKEN)
        {
            return PARSER_UNEXPECTED_TOKEN;
        }
        add_child_to_parent(new_list, ast_node);

        if (lexer->current_tok->type == TOKEN_NL)
        {
            free(lexer_pop(lexer));
        }
    }
    return PARSER_OK;
}

/*
    simple_command = WORD { element } ;
*/
enum parser_status parse_simple_command(struct lexer *lexer, struct ast **node)
{
    struct ast *new_cmd = ast_genesis(AST_CMD);
    if (lexer->current_tok->type == TOKEN_WORD && parse_element(lexer, new_cmd) == PARSER_OK)
    {
        *node = new_cmd;
        return PARSER_OK;
    }
    else
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}

/*
    element = WORD ;
*/
enum parser_status parse_element(struct lexer *lexer, struct ast *node)
{
    char **data = node->data;
    if (lexer->current_tok->type == TOKEN_WORD)
    {
        struct token *start = lexer_pop(lexer);
        data = add_to_data(data, start->value);
        free(start);
        while (lexer->current_tok->type == TOKEN_WORD)
        {
            struct token *tmp = lexer_pop(lexer);
            data = add_to_data(data, tmp->value);
            free(tmp);
        }
        node->data = data;
        return PARSER_OK;
    }
    else
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}
