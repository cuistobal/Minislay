#include "minislay.h"

// '(' CommandList ')'
bool	parse_compound_command(t_tokn **current)
{
	t_tokn	*save;

	save = *current;
    if ((*current)->type == OPAR)
	{
        *current = (*current)->next;
        if (parse_command_list(current))
		{
			if ((*current)->type == CPAR)
			{
        	    *current = (*current)->next;
        	    return (true);
        	}
		}
		printf("Syntax error: Expected XXXX token.\n");
		return (false);
    }
	*current = save;
    return (false);
}

