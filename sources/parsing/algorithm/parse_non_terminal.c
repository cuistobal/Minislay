/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_non_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:54:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 17:24:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
// SimpleCommand → Assignment* WORD (Argument | Redirection)*
// The WORD element in the middle is not mandatory.
bool	parse_simple_command(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
	//	if (valid_lexeme(*current, OPAR, LORR | OPAR))
	//		return (false);
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
			set_state(&parser->state, PIPELIN);
			consume_token(current, parser);
			if (*current)
				return (parse_command(current, parser));
		}
		return (true);
	//	return (parsing_error((*current)->value));
	}
	return (!*current);
}


//We can return false -> It's the last sub funciton that aprse command goes
//Actually (?)
bool	parse_compound_command(t_tokn **current, t_pars *parser)
{
	if (is_state_active((*current)->type, OPAR))
	{
//		if ((*current)->next && is_state_active((*current)->next->type, CPAR))
//			return (false);

		set_state(&(parser)->state, SUBSHEL);
		consume_token(current, parser);
		if (parse_command_list(current, parser))
		{
			if ((*current) && (*current)->type & CPAR)
				return (consume_token(current, parser));
		}
//		if (!is_state_active(parser->state, SUBSHEL))
//			return (parsing_error((*current)->value));
	}
	return (true);
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
}*/

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
			set_state(&parser->state, PIPELIN);
			consume_token(current, parser);
			if (*current)
				return (parse_command(current, parser));
			return (error_message(SYNTAX), error_message(UNEXPECTED));
		}
		return (true);
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

