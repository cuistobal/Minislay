#include "minislay.h"

// Assignment → WORD '=' Expression
bool	parse_assignment(t_tokn **current)
{
    if ((*current) && (*current)->type & EQUL)
	{
		*current = (*current)->next;
		return (true);
	}
    return (false);
	//return false or return
	//return (*current == NULL);
}

// Argument → WORD
bool	parse_argument(t_tokn **current)
{
    if ((*current) && (*current)->type & WORD)
	{
       	*current = (*current)->next;
        return (true);
    }
    return (false);
	//return false or return
	//return (*current == NULL);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current)
{
	t_tokn	*save;

	save = NULL;
    if ((*current)->type >= IRED && (*current)->type <= ARED)
	{
		save = *current;
        *current = (*current)->next;
        if (*current)
		{
			if ((*current)->type & WORD)
			{
        	    *current = (*current)->next;
        	    return (true);
        	}
			printf("Syntax error: Unexpected %s token after %s token.\n", (*current)->value, save->value);
			return (false);
		}
		printf("Syntax error: Expected WORD token after %s token.\n", save->value);
		return (false);
    }
    return (false);
}
