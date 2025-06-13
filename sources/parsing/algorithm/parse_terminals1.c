/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_terminals1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:54:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 18:42:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (current)
	{
		if (parse_assignment(current, parser))
			return (assignations(current, parser));
		return (false);
	}
	return (!*current);
}
