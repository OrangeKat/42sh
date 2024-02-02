#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *file_to_string(int *fd, char *buffer, size_t capacity)
{
    size_t length = 0;
    char tmp_buff[1];
    while (read(*fd, tmp_buff, 1) > 0)
    {
        if (length + 1 == capacity)
        {
            capacity *= 2;
            buffer = realloc(buffer, capacity);
            if (!buffer)
            {
                free(buffer);
                return NULL;
            }
        }
        buffer[length++] = tmp_buff[0];
    }
    buffer[++length] = '\0';
    return buffer;
}

int dot(char **data)
{
    int fd = open(data[1], O_RDONLY);
    size_t capacity = 64;
    char *cmd = malloc(capacity);
    cmd = file_to_string(&fd, cmd, capacity);
}
