#include "minislay.h"

//
//
//

//Move to utils
static bool append_list_value(t_tokn *token, char *expanded)
{
    if (expanded && token)
    {
		if (token->value)
        	free(list->value); 
    	token->value = expanded;
    }
    return (expanded);
}

//
static bool append_expanded(char **expanded, char *buffer, int blen, int index)
{
	int		diff;
	char	*temp;
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
static bool	expand_buffer(t_shel *minishell, char **buffer)
{
	char	*value;

	value = NULL;
	if (find_key(minishell, &value, *buffer))
	{
		free(*buffer);
		*buffer = strdup(value);
		return (*buffer);
	}
	else
	{
		free(*buffer);
		*buffer = strdup("");		//Remove this magic number
		return (*buffer);	
	}
	return (false);
}

static bool	copy_and_reset_buffer(char **expanded, char **buffer, int *blen, int *index)
{
	char	*temp;

	temp = NULL;
	if (*expanded && *buffer)
	{
			
		return (true);
	}
	return (false);
}

//
static bool get_expanded(t_shel *minishell, t_tokn *token)
{
    int     blen;
    int     index;
	int		total;
    char    *buffer;
    char    *expanded;
    
    blen = 0;
    index = 0;
    buffer = NULL;
    expanded = strdup(token->value);
	if (expanded)
	{
		total = strlen(expanded);
    	while (find_expansions(&buffer, expanded, &index, &blen))
    	{
			if (expand_buffer(minishell, &buffer))
			{
				if (!copy_and_reset_buffer())
					return (false);
			}
			index += blen;
			blen = 0;
			}
		}
	}
	return (expanded);
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn *list)
{
	while (list)
	{
		if ((list)->type & DOLL)
    	{
        	if (!get_expanded(minishell, list))
				return (false);
    	}
        move_pointer(&list);
    }
	return (!list);
}
