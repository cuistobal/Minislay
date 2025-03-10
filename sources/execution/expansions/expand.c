#include "minislay.h"

//
static bool append_list_value()
{
    if (expanded)
    {
        free(list->value); 
        list->value = expanded;
    }
    return (expanded);
}

//
static bool append_expanded(char **expanded, char *buffer, )
{
    char    *merged;

    merged = NULL;
    if (*expanded)
    {
        *expanded = (char *)realloc(*expanded)
    }
    else
        *expanded = strdup(buffer);
    return (*expanded);
}
//
static bool get_expanded(t_shel *minishell, t_tokn **list)
{
    int     blen;
    int     index;
    char    *buffer;
    char    *expanded;
    
    blen = 0;
    index = 0;
    buffer = NULL;
    expanded = NULL;
    while (find_expansions(&buffer, list->value, &index, &blen))
    {
        if (!valid_variable(buffer))
        {
            free(buffer);
            return (false);
        }
        else
        {
            append_expand(&expanded, buffer);
        }
    }
    return (append_list_value());
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn *list)
{
    if (minishell)
    {
        while (list)
        {
            if (list->type & DOLL)
            {
                if (!get_expanded(list))
                    return (false);
            }
            move_pointer(&list);
        }
        return (!list);
    }
    return (minishell);
}
