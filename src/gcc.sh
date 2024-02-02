gcc -fPIC -coverage -g -fsanitize=address -Werror -Wall -Wextra -Wvla -std=c99 -pedantic main.c lexer_parser/lexer/lexer.c lexer_parser/parser/parser_utils.c lexer_parser/parser/parser.c lexer_parser/ast/ast.c lexer_parser/eval/eval.c builtins/echo.c utils/token_utils.c builtins/true.c builtins/false.c lexer_parser/eval/pipe.c lexer_parser/eval/redir.c builtins/cd.c builtins/exit.c utils/variable.c -lgcov
