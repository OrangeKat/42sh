#include <string.h>

#include "file_to_string.h"

int main(void)
{
    FILE *s = fopen("test", "w");
    char *res = file_to_string(s);
    printf("%s\n", res);
    return 0;
}
