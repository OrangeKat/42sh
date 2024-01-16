# Name of the libraries
lib_LIBRARIES = liblexpar.a

# List of files to compile in liblexpar.a
liblexpar_a_SOURCES= \
	ast/ast.c \
	ast/ast.h \
	lexer/lexer.c \
	lexer/lexer.h \
	lexer/lexer.h \
	parser/parser.c \
	parser/parser.h \
	eval/ast_print.c \
	eval/rpn_print.c \
	eval/token_printer.c \

liblexpar_a_CPPFLAGS = -I(top_srcdir)/src
liblexpar_a_CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla -pedantic
