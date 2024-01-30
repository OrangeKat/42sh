#include <stdlib.h>

#include "builtin.h"

unsigned int bin_exit(char **args, size_t argnum)
{
    if (argnum != 2)
    {
        return 1;
    }
    return atoi(args[1]);
}