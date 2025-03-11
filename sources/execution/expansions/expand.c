#include "minislay.h"

//
//
//

//Move to utils
static bool append_list_value()
{
    if (expanded)
    {
        free(list->value); 
        list->value = expanded;
    }
    return (expanded);
}

//Move to utils
bool	check_env_struct(t_shel *minishell)
{
	if (minishell)
	{

	}
}

//
static bool append_expanded(char **expanded, char *buffer, int blen)
{
    char    *merged;

    merged = NULL;
    if (*expanded)
    {
        merged = 
        *expanded = (char *)realloc(*expanded)
    }
    else
        *expanded = strdup(buffer);
    return (*expanded);
}

//
static bool	expand_buffer(t_shel *minishell, char **expanded, char *buffer)
{
	if (minishell)
	{

		if (minishell->expt)
		{
			//Try to retrieve the buffer's value within environement variables.
		}

		else if (minishell->local)
		{
			//Try to retrieve the buffer's value within local variables.
		}
		
		//expanded = strup 
	}
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
    while (find_expansions(&buffer, (*list)->value, &index, &blen))
    {
		/*	USELESS TO CHECK IT -> RULES APPLIES FOR ASSIGNASTIONS
        if (!valid_variable(buffer))
        {
            //leaks
            free(buffer);
            return (false);
        }
        else
        {*/
            if (!expand_buffer(minishell, &expanded, buffer))
                //leaks
                return false;
            append_expand(&expanded, buffer);
	//	}
    }
    return (append_list_value());
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn **list)
{
    if (minishell)
    {
        while (*list)
        {
            if ((*list)->type & DOLL)
            {
                if (!get_expanded(list))
                    return (false);
            }
            move_pointer(list);
        }
        return (!*list);
    }
    return (minishell);
}
