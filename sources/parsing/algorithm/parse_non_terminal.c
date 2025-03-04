#include "minislay.h"

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
// The WORD element in the middle is not mandatory.
bool	parse_simple_command(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		assignations(current, parser);
		return (argument_or_redirection(current, parser));
    }
	return (!*current);
}

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if ((*current)->type & PIPE)	
		{
			if ((*current)->type != PIPE)
			{
				set_state(&parser->state, PIPELIN);
				consume_token(current, parser);
				if (*current)
					return (parse_command(current, parser)); 	
				printf("Invalid syntax, expected token after PIPE token.\n");		
				return (false);
			}
			// Invalid syntax
			return ((*current)->next);
		}
        return (true); //A retravailler
	}
	return (!*current);
}

//We can return false -> It's the last sub funciton that aprse command goes
//Actually (?)
bool	parse_compound_command(t_tokn **current, t_pars *parser)
{
	if ((*current)->type == OPAR)
	{
		set_state(&(parser)->state, SUBSHEL);
		consume_token(current, parser);
		if (parse_command_list(current, parser))
		{
			if ((*current) && (*current)->type & CPAR)
				return (consume_token(current, parser));
		}
	}
	return (false);
}

//
bool	parse_command(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (!parse_compound_command(current, parser))
		{
			if (!parse_simple_command(current, parser))
				return (parse_pipeline(current, parser));
		}
	}
	return (!*current);
}
