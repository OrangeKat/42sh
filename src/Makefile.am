SUBDIRS = builtins \
		  lexer_parser

bin_PROGRAMS = 42sh

42sh_SOURCES = main.c

42sh_CPPFLAGS = -I%D%

42sh_CFLAGS = -std=c99 -Wall -Wextra -Werror -Wvla -pedantic

42sh_LDADD = \
	builtins/libbin.a \
	lexer_parser/liblexpar.a \
	utils/libutils.a
