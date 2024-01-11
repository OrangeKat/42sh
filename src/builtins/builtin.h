#ifndef BUILTIN_H
#define BUILTIN_H

#include <stddef.h>

int bin_true(void);
int bin_false(void);
int echo(char *args[], size_t argnum, int extend, int newline);

#endif // BUILTIN_H
