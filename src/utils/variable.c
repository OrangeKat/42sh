#include "variable.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define SA 0
#define SSTAR 1
#define SQM 2
#define SS 3
#define NMB_SPECIAL_VARS 4
#define SOLDPWD 0
#define SPWD 1
#define SIFS 2
#define NMB_ENV_VARS 3

struct var_holder *init_var_holder(void)
{
    struct var_holder *vh = malloc(sizeof(struct var_holder));
    vh->uvar_names = calloc(1, sizeof(char *));
    vh->uvar_values = calloc(1, sizeof(char *));
    vh->spec_values = malloc(sizeof(char *) * NMB_SPECIAL_VARS);
    vh->arg_values = NULL;
    vh->env_values = malloc(sizeof(char *) * NMB_ENV_VARS);
    return vh;
}

void destroy_holder(struct var_holder *vh)
{
    size_t i = 0;
    while (vh->uvar_names[i] != NULL)
    {
        free(vh->uvar_names[i]);
        i++;
    }
    free(vh->uvar_names[i]);
    free(vh->uvar_names);

    i = 0;
    while (vh->uvar_values[i] != NULL)
    {
        free(vh->uvar_values[i]);
        i++;
    }
    free(vh->uvar_values[i]);
    free(vh->uvar_values);

    for (size_t j = 0; j < NMB_SPECIAL_VARS; j++)
    {
        free(vh->spec_values[j]);
    }
    free(vh->spec_values);

    for (size_t k = 0; k < NMB_SPECIAL_VARS; k++)
    {
        free(vh->env_values[k]);
    }
    free(vh->env_values);
}

size_t access_variable(char *name, struct var_holder *vh)
{
    size_t i = 0;
    while (vh->uvar_names[i] != NULL)
    {
        if (strcmp(name, vh->uvar_names[i]) == 0)
        {
            return i;
        }
    }
    return i;
}

int set_variable(char *name, char *value, struct var_holder *vh)
{
    size_t index = access_variable(name, vh);
    if (vh->uvar_names[index] == NULL)
    {
        vh->uvar_names = realloc(vh->uvar_names, (index + 2) * sizeof(char *));
        vh->uvar_names[index] = name;
        vh->uvar_names[index + 1] = NULL;
    }
    vh->uvar_values[index] = value;
    return 0;
}

char *get_variable(char *name, struct var_holder *vh)
{
    size_t index = access_variable(name, vh);
    if (vh->uvar_names[index] == NULL)
    {
        // error handling
    }
    return vh->uvar_values[index];
}
