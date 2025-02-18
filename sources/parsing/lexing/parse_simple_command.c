#include "minislay.h"

static bool	argument_or_redirection(t_tokn **current)
{
	if (*current)
	{
		if (!parse_redirection(current))
		{
			if (parse_argument(current))
				Tretun (argument_or_redirection(current));
			return (false);
		}
		return (argument_or_redirection(current));
	}
	return (current != NULL);
}

static bool	assignations(t_tokn **current)
{
	if (*current)
	{
		if (parse_assignment(current))
			return (assignations(current));
		return (false);
	}
	return (current != NULL);

}

bool	parse_simple_command(t_tokn **current)
{
	if (*current)
	{
		assignations(current);
		return (argument_or_redirection(current));
	}
    return (*current == NULL);
}
