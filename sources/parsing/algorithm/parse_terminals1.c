#include "minislay.h"

//
bool	argument_or_redirection(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (!parse_redirection(current, parser))
		{
			if (parse_argument(current, parser))
				return (argument_or_redirection(current, parser));
			return (false);
		}
		return (argument_or_redirection(current, parser));
	}
	return (!*current);
}

//
bool	assignations(t_tokn **current, t_pars *parser)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (current)
	{
		if (parse_assignment(current, parser))
			return (assignations(current, parser));
		return (false);
	}
	return (!*current);

}
