#include "parser.h"

#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

static void add_to_data(char **data, char *word)
{
    size_t length = 0;
    while (data[length])
    {
        length++;
    }
    data[length] = word;
    length++;

    data = realloc(data, length);
    data[length - 1] = NULL;
}

/*
    input =
    simple_command '\n'
    | simple_command EOF
    | '\n'
    | EOF
    ;
*/
enum parser_status parse(struct ast **tree_list, struct lexer *lexer, size_t curr_root)
{
    struct ast *ast_node = NULL;
    if (lexer->current_tok->type == TOKEN_NL)
    {
        free(lexer_pop(lexer));
        tree_list = realloc(tree_list, curr_root + 2);
        parse(tree_list, lexer, curr_root + 1);
        return PARSER_OK;
    }
    else if (lexer->current_tok->type == TOKEN_EOF)
    {
        free(lexer_pop(lexer));
        return PARSER_OK;
    }
    else if (parse_simple_command(lexer, ast_node) == PARSER_OK)
    {
        tree_list[curr_root] = ast_node;
        parse(tree_list, lexer, curr_root);
        return PARSER_OK;
    }
    else 
    {
        lexer_destroy(lexer);
        return PARSER_UNEXPECTED_TOKEN;
    }
}

/*
    simple_command = WORD { element } ;
*/
enum parser_status parse_simple_command(struct lexer *lexer, struct ast *node)
{
    struct ast *new_cmd = ast_genesis(AST_CMD);
    if (lexer->current_tok == TOKEN_WORD && parse_element(lexer, new_cmd->data) == PARSER_OK)
    {
        node = new_cmd;
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
enum parser_status parse_element(struct lexer *lexer, char **data)
{
    if (lexer->current_tok->type == TOKEN_WORD)
    {
        struct token *start = lexer_pop(lexer);
        add_to_data(data, start->value);
        free(start);
        while (lexer_peek(lexer)->type == TOKEN_WORD)
        {
            struct token *tmp = lexer_pop(lexer);
            add_to_data(data, tmp->value);
            free(tmp);
        }
        return PARSER_OK;
    }
    else
    {
        return PARSER_UNEXPECTED_TOKEN;
    }
}
