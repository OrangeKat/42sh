#ifndef VARIABLE_H
#define VARIABLE_H

struct var_holder
{
    char **uvar_names;
    char **uvar_values;
    char **spec_values;
    char **arg_values;
    char **env_values;
};

struct var_holder *init_var_holder(void);

void destroy_holder(struct var_holder *vh);

int set_variable(char *name, char *value, struct var_holder *vh);

char *get_variable(char *name, struct var_holder *vh);

#endif /* VARIABLE_H */
