SUBDIRS = src \
		  tests

debug: CFLAGS+= -g -fsanitize=address
debug: all

check: CFLAGS+= -fPIC -coverage -O0 -fprofile-arcs -ftest-coverage
check: LDLIBS+= -lgcov

clean:
	@rm -rf config.log config.status configure configure~ \
		install-sh install-sh~ depcomp missing \
		aclocal.m4 ar-lib autom4te.cache/ compile \
		doc/html \
		src/42sh \
		Makefile Makefile.in \
		*/Makefile */Makefile.in \
		src/*/Makefile src/*/Makefile.in \
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
		test-driver \
		tests/test-suite.log \
		tests/*/*/*.sh.log tests/*/*/*.sh.trs

.PHONY = clean debug
