/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_terminals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:59:00 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 14:08:01 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Assignment → WORD '=' Expression -> Implemtanton a revoir
// Finalement → EQUL 
bool	parse_assignment(t_tokn **current, t_pars *parser)
{
	if ((*current) && (*current)->type & EQUL)
		return (consume_token(current, parser));
	return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current, t_pars *parser)
{
	if ((*current) && (*current)->type & WORD)
		return (consume_token(current, parser));
	return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (valid_lexeme(*current, HDOC, ARED | OPAR))
		{
			consume_token(current, parser);
			if ((*current))
			{
				if ((*current)->type & WORD)
					return (consume_token(current, parser));
				return (error_message(SYNTAX), error_message(UNEXPECTED), \
						error_message((*current)->value));
			}
			*current = (parser)->tab[TTPREV];
			error_message(SYNTAX);
			error_message(UNEXPECTED);
			error_message((*current)->value);
		}
	}
	return (!*current);
}

// Edge case $ seul + gerer 
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current, t_pars *parser)
{
	if ((*current)->type & DOLL && (*current)->type < SQTE)
		return (consume_token(current, parser));
	return (parse_argument(current, parser));
}
