#ifndef VARIABLE_H
#define VARIABLE_H

#include <stddef.h>

enum var_type
{
    INT = 0,
    STRING,
    LIST,
    DELIM,
};

union var_value
{
    int numb;
    char *string;
    char **list;
};

struct var
{
    enum var_type type;
    union var_value data;
    char *name;
};

struct var_holder
{
    struct var *user_variables;
    size_t size;
    struct var spec_variables[4];
    struct var *arg_variables;
    struct var env_variables[4];
};

struct var init_var(char *data, enum var_type type, char *name);

struct var_holder *init_var_holder(void);

void destroy_holder(struct var_holder *vh);

int set_variable(char *name, char *value, enum var_type type,
                 struct var_holder *vh);

struct var get_variable(char *name, struct var_holder *vh);

#endif /* VARIABLE_H */
