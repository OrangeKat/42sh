gcc -g -fsanitize=address -Werror -Wall -Wextra -Wvla -std=c99 -pedantic main.c lexer_parser/lexer/lexer.c lexer_parser/parser/parser.c lexer_parser/ast/ast.c lexer_parser/eval/eval.c builtins/echo.c utils/token_utils.c builtins/true.c builtins/false.c
