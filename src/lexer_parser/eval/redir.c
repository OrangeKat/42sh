#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lexer.h"

void redirect_to_file(char **data)
{
    
}
void redirect_to_stdin(data[2])
{

}

void redirect_to_end_of_file(data[2])
{

}

void redirect_to_fd(data[2])
{

}

void redirect_fd_to_fd(data[2])
{

}

void redirect_to_file(data[2])
{

}

void redirect_open_and_write(data[2])
{
    
}

void select_pipe(char **data)
{
    if(strcmp(data[1],">")==0)
    {
        redirect_to_file(data[2]);
    }
    if(strcmp(data[1],"<")==0)
    {
        redirect_to_stdin(data[2]);
    }
    if(strcmp(data[1],">>")==0)
    {
        redirect_to_end_of_file(data[2]);
    }
    if(strcmp(data[1],">&")==0)
    {
        redirect_to_fd(data[2]);
    }
    if(strcmp(data[1],"<&")==0)
    {
        redirect_fd_to_fd(data[2]);
    }
    if(strcmp(data[1],">|")==0)
    {
        redirect_to_file(data[2]);
    }
    if(strcmp(data[1],"<>")==0)
    {
        redirect_open_and_write(data[2]);
    }
}