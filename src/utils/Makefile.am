# Name of the libraries
lib_LIBRARIES = libutils.a

# List of files to compile in libutils.a
libutils_a_SOURCES= \
	file_to_string.c \
	token_utils.c \
	file_to_string.h \
	token_utils.h \
	variable.c \
	variable.h

libutils_a_CPPFLAGS = -I$(top_srcdir)/src
libutils_a_CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla -pedantic

noinst_LIBRARIES = libutils.a
