/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_parenthesis_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:35:05 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/03 13:03:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void set_state(t_parser *parser, int new_state)
{
    parser->state |= new_state; // Activate new state
}

void unset_state(t_parser *parser, int old_state)
{
    parser->state &= ~old_state; // Deactivate old state
}

bool	is_state_active(char state, size_t check_state)
{
    return (parser->state & check_state); // Check if a state is active
}

static bool	stack_operation()
{

}

static int	check_syntax(char input)
{
	if (input == OPAR)
		return (0);
	else if (input == SQTE)
		return (1);
	else if (input == DQTE)
		return (2);
	else if (input == CPAR)
		return (3);
	return (4);
}

bool	check_quotes_and_parenthesis(t_pars *parser)
{
	size_t	type;
	size_t	index;

	if (parser)
	{
		type = 0;
		index = 0;
		if (parser->input)
		{
			while (parser->input[index]) // && parser->state != ERROR
			{
				type = check_syntax(parser->input[index]);
				if (type < 4) // Remplacer 4
				{
					if (is_state_active(parser, type))
						stack_operation();
				}
				i++;
			}
			return (true); // (parser->state != ERROR);
		}
	}
	return (false);
}
