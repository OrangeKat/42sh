#include "parser.h"

#include <stdlib.h>

#include "../ast/ast.h"
#include "../lexer/lexer.h"

static char **add_to_data(char **data, char *word)
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

static int list_node_continue(enum token_type type)
{
    switch (type)
    {
    case TOKEN_EOF:
        return 0;
    case TOKEN_THEN:
        return 0;
    case TOKEN_FI:
        return 0;
    case TOKEN_ELSE:
        return 0;
    case TOKEN_ELIF:
        return 0;
    default:
        return 1;
    }
}

/*
    element = WORD ;
*/
static enum parser_status parse_element(struct lexer *lexer, struct ast *node)
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
        return PARSER_NOK;
    }
}

/*
    redirection = [IONUMBER] ( '>' |  '<' | '>>' | '>&' | '<&' | '>|' | '<>' )
   WORD ;
*/
/*static enum parser_status parse_redirection(struct lexer *lexer,struct ast
**node)
{
    struct ast *new_redir = ast_genesis(AST_REDIR);
    char **data = new_redir->data;
    if (lexer->current_tok->type == TOKEN_REDIR)
    {
        struct token *start = lexer_pop(lexer);
        data = add_to_data(data, start->value);
        free(start);
        *node = new_redir;
        return PARSER_OK;
    }
    else
    {
        *node = new_redir;
        return PARSER_NOK;
    }
}*/
/*
    prefix = redirection ;
*/
/*static enum parser_status parse_prefix(struct lexer *lexer,struct ast **node)
{
    if(parse_redirection(lexer,node) == PARSER_OK)
    {
        return PARSER_OK;
    }
    else
    {
        return PARSER_NOK;
    }
}*/
/*
    simple_command =
        prefix { prefix }
    |   { prefix } WORD { element }
    ;
    //TODO : add redir to simple command and do the prefix and redir parser
*/
static enum parser_status parse_simple_command(struct lexer *lexer,
                                               struct ast **node)
{
    struct ast *new_cmd = ast_genesis(AST_CMD);
    if (lexer->current_tok->type == TOKEN_WORD
        && parse_element(lexer, new_cmd) == PARSER_OK)
    {
        *node = new_cmd;
        return PARSER_OK;
    }
    else
    {
        return PARSER_NOK;
    }
}

/*
    compound_list = pipeline { ; pipeline } [ ; ] ;
*/
static enum parser_status parse_compound_list(struct lexer *lexer,
                                              struct ast **node)
{
    struct ast *new_clist = ast_genesis(AST_LIST);
    *node = new_clist;
    while (list_node_continue(lexer->current_tok->type))
    {
        struct ast *ast_node = NULL;
        if (parse_pipeline(lexer, &ast_node) == PARSER_NOK)
        {
            return PARSER_NOK;
        }
        new_clist = add_child_to_parent(new_clist, ast_node);

        if (lexer->current_tok->type == TOKEN_NL)
        {
            free(lexer_pop(lexer));
        }
    }
    return PARSER_OK;
}

/*
    rule_if = 'if' compound_list 'then' compound_list [else_clause] 'fi' ;

    else_clause =
        'else' compound_list
    |   'elif' compound_list 'then' compound_list [else_clause]
    ;
*/
static enum parser_status parse_if_else(struct lexer *lexer, struct ast **node)
{
    struct ast *new_if = ast_genesis(AST_IF);
    *node = new_if;
    free(lexer_pop(lexer));

    struct ast *condition_list = NULL;
    if (parse_compound_list(lexer, &condition_list) == PARSER_NOK)
    {
        return PARSER_NOK;
    }
    new_if = add_child_to_parent(new_if, condition_list);
    free(lexer_pop(lexer));

    struct ast *then_list = NULL;
    if (parse_compound_list(lexer, &then_list) == PARSER_NOK)
    {
        return PARSER_NOK;
    }
    new_if = add_child_to_parent(new_if, then_list);

    struct ast *else_list = NULL;
    if (lexer->current_tok->type == TOKEN_ELSE
        || lexer->current_tok->type == TOKEN_ELIF)
    {
        free(lexer_pop(lexer));
        if (parse_compound_list(lexer, &else_list) == PARSER_NOK)
        {
            return PARSER_NOK;
        }

        if (lexer->current_tok->type != TOKEN_FI)
        {
            return PARSER_NOK;
        }
        free(lexer_pop(lexer));
    }
    else
    {
        if (lexer->current_tok->type != TOKEN_FI)
        {
            return PARSER_NOK;
        }
        free(lexer_pop(lexer));

        if (parse_compound_list(lexer, &else_list) == PARSER_NOK)
        {
            return PARSER_NOK;
        }
    }

    if (else_list)
    {
        new_if = add_child_to_parent(new_if, else_list);
    }

    return PARSER_OK;
}

/*
    command =
        simple_command
    |   shell_command {redirect}
    ;
*/
static enum parser_status parse_command(struct lexer *lexer, struct ast **node)
{
    if (lexer->current_tok->type == TOKEN_IF)
    {
        return parse_if_else(lexer, node);
    }
    else if (lexer->current_tok->type == TOKEN_REDIR
             || lexer->current_tok->type == TOKEN_WORD)
    {
        return parse_simple_command(lexer, node);
    }
    else
    {
        return PARSER_NOK;
    }
}

/*
    pipeline = ['!'] command { '|' {'\n'} command } ;
*/
enum parser_status parse_pipeline(struct lexer *lexer, struct ast **node)
{
    if (lexer->current_tok->type == TOKEN_NOT)
    {
        struct ast *new_not = ast_genesis(AST_NOT);
        *node = new_not;
        free(lexer_pop(lexer));
    }

    struct ast *new_pipe = ast_genesis(AST_PIPE);
    struct ast *new_child = NULL;
    if (parse_command(lexer, &new_child) == PARSER_NOK)
    {
        ast_destroy(new_pipe);
        return PARSER_NOK;
    }
    new_pipe = add_child_to_parent(new_pipe, new_child);

    while (lexer->current_tok->type == TOKEN_PIPE)
    {
        free(lexer_pop(lexer));
        new_child = NULL;
        if (parse_command(lexer, &new_child) == PARSER_NOK)
        {
            ast_destroy(new_pipe);
            return PARSER_NOK;
        }
        new_pipe = add_child_to_parent(new_pipe, new_child);
    }

    if (*node == NULL)
    {
        *node = new_pipe;
    }
    else
    {
        *node = add_child_to_parent(*node, new_pipe);
    }

    return PARSER_OK;
}

/*
    list = pipeline;
*/
static enum parser_status parse_list(struct lexer *lexer, struct ast **node)
{
    struct ast *new_list = ast_genesis(AST_LIST);
    *node = new_list;
    while (list_node_continue(lexer->current_tok->type))
    {
        struct ast *ast_node = NULL;
        if (parse_pipeline(lexer, &ast_node) == PARSER_NOK)
        {
            return PARSER_NOK;
        }
        new_list = add_child_to_parent(new_list, ast_node);

        if (lexer->current_tok->type == TOKEN_NL)
        {
            free(lexer_pop(lexer));
        }
    }
    return PARSER_OK;
}

/*
    input =
        list '\n'
    |   list EOF
    |   '\n'
    |   EOF
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
        return PARSER_NOK;
    }
}
