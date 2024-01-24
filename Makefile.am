SUBDIRS = src \
		  tests

debug: CFLAGS+= -g -fsanitize=address
debug: all

clean:
	rm -rf config.log config.status configure configure~ \
		install-sh install-sh~ depcomp missing \
		aclocal.m4 ar-lib autom4te.cache/ compile \
		doc/html \
		src/42sh \
		Makefile Makefile.in \
		src/Makefile src/Makefile.in \
		src/builtins/Makefile src/builtins/Makefile.in \
		src/lexer_parser/Makefile src/lexer_parser/Makefile.in \
		src/utils/Makefile src/utils/Makefile.in \
		src/*/*.a \
		src/*.o \
		src/*/*.o \
		src/*/*/*.o \
		src/.deps \
		src/*/.deps \
		src/*/*/.deps \
		src/.dirstamp \
		src/*/.dirstamp \
		src/*/*/.dirstamp \
		test-driver

.PHONY = clean debug
