/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:09:21 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 15:09:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool	ignore_nested_operators(t_tokn **current, t_pars *parser)
{
	if ((*current) && valid_lexeme(*current, LAND, LORR | OPAR))
	{
		if ((*current)->type & OPAR)
		{
			consume_token(current, parser);
			return (parse_command_list(current, parser));
		}
		else
		{
			set_state(&parser->state, ROOTEDD);
			return ((*current)->next);
		}
	}
	return (*current);
}

//
bool	parse_command_list(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (parse_command(current, parser))
		{
			if (*current)
			{
				while ((*current) && (*current)->type & CPAR)
					consume_token(current, parser);
				return (ignore_nested_operators(current, parser));
			}
		}
	}
	return (!*current);
}

//This is the entry of our parsing module. It identifies the first non 
//parethesed significant operator and builds the tree's root out of it
bool	parse_script(t_pars **parser)
{
	t_tokn	*current;
	
	current = (*parser)->tab[TTHEAD];
	if (current)
	{
		append_token_tab((*parser)->tab, current, TTCURR);	
		if (parse_command_list(&current, *parser))
		{
			if (current)
				append_token_tab((*parser)->tab, current->next, TTNEXT);
			return (build_ast(parser));
		}
	}
	return (!(*parser)->tab[TTHEAD]);	
}
