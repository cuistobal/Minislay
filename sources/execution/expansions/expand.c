#include "minislay.h"

//
static bool	expand_buffer(t_shel *minishell, char **buffer)
{
	char	*value;

	value = NULL;

	//Implemeter is_special_expansion() pour gerer le $$, $? etc

	if (find_key(minishell, &value, *buffer + 1))
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
	char	*merged;
	size_t	new_len;

	temp = NULL;
	merged = NULL;
	if (*expanded && *buffer)
	{
		new_len = strlen(*buffer);
		temp = strndup(*expanded, *index);
		if (temp)
		{
			merged = ft_strjoin(temp, *buffer);
			if (merged)
			{
				free(temp);
				*index += new_len;
				temp = strdup(*expanded + *index);
				merged = ft_strjoin(merged, temp);
				if (merged)
				{
					free(*expanded);
					*expanded = merged;
				}
				free(temp);
				temp = NULL;
				*blen = 0;
			}
		}
	}
	return (merged);
}

/*		OLD
//
static char    *expansion(char *token, int *index, int *blen)
{
    while (token[*index + *blen] && !strchr(LIMITERS, token[*index + *blen]))
    {
        (*blen)++;

		if (strchr(SPECIALS, token[*index + *blen]))
        {
            (*blen)++;
            break ;
        }
    }
    return (strndup(token + *index, *blen));
}*/

static char    *expansion(char *token, int *index, int *blen)
{
    while (*blen < *index)
    {
        (*blen)++;
		if (strchr(SPECIALS, token[*blen]))
            break ;
    }
    return (strndup(token, *blen));
}

//
static bool    find_expansions(char **buffer, char *token, int *index, int *blen)
{
	int		start;
	bool	dollar;

	start = *index;
	dollar = false;
    if (token && token[*index])
   	{
		while (token[*index])
		{
			if (strchr(SPECIALS, token[*index]))
			{
				if (dollar && *index != start)
					break ;
				dollar = token[*index] == '$';
			}
			(*index)++;
		}
	//	if (token[*index])
        {
			*buffer = expansion(token, index, blen);
            return (*buffer);
      	}
    }
	return false;
}

/*
static bool    find_expansions(char **buffer, char *token, int *index, int *blen)
{
	bool	dollar;
	
	dollar = false;
	while (*token)
	{
		if (*token == '$')
		{
			if (dollar)
				break ;
			dollar = true;
		}
		token++;
		(*index)++;
	}
	printf("%c	%d\n", token[*index], *index);
	if (*token)
    {
		*buffer = expansion(token, index, blen);
        return (*buffer);
    }
	return false;
  //  return (token);
}*/

//
static bool get_expanded(t_shel *minishell, t_tokn **token)
{
    int     blen;
    int     index;
    char    *buffer;
    char    *expanded;
    
    blen = 0;
    index = 0;
    buffer = NULL;
	expanded = strdup((*token)->value);
//	expanded = (*token)->value;
	if (expanded)
	{
		while (find_expansions(&buffer, expanded, &index, &blen))
		{
			if (expand_buffer(minishell, &buffer))
			{
				if (!copy_and_reset_buffer(&expanded, &buffer, &blen, &index))
					return (false);
			//	index++;
			}
			//printf("%d	->	%s\n", index, expanded);
		}
		free((*token)->value);
		(*token)->value = expanded;
	//	printf("%s\n", expanded);
		return true;
	}
	//error message Memalloc failure
	return false;
//	return (expanded);
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn **list)
{
	while (*list)
	{
		if ((*list)->type & DOLL)
    	{
        	if (!get_expanded(minishell, list))
				return (false);
    	}
        move_pointer(list);
    }
	return (!*list);
}
