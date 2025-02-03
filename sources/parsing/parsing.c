/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:39:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/03 09:48:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static t_pars	*initialiase_parsing_structure(char *input)
{
	t_pars	*new;

	new = (t_parse *)malloc(sizeof(t_pars));
	if (new)
	{
		new->input = input;
		new->stack = NULL;
		new->syntax[0] = OPAR;
		new->syntax[1] = SQTE;
		new->syntax[2] = DQTE;
		new->syntax[3] = CPAR;
		new->state = STATE_NORML;
	}
	return (new);
}

bool	parsing(char *input)
{
	t_pars	*parser;
	char	*collapsed;

	parser = NULL;
	collapsed = NULL;
	if (input)
	{
		collapsed = ft_strdup(input);
		if (collapsed)
		{
			whitespaces_collapsing(input, collapsed);
			parser = initialise_parsing_structure(collapsed);
			if (parser)
			{
				if (check_quotes_and_parenthesis(parser))
					return (free(parser), true);
			}
		}
	}
	return (false);
}
