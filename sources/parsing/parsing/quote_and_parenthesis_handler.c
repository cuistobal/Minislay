/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_parenthesis_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:35:05 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/03 11:11:12 by chrleroy         ###   ########.fr       */
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

static bool	check_state()
{
	
}

static bool	check_syntax(int *index, char syntax[], char input)
{
	if (input)
	{
		if (syntax)
		{
			while (syntax[*index])
			{
				if (syntax[*index] == input)
					return (true);
				(*index)++;
			}
		}
	}
	return (false);
}

bool	check_quotes_and_parenthesis(t_pars *parser)
{
	size_t	i;
	size_t	hash_i;

	if (parser)
	{
		i = 0;
		if (parser->input)
		{
			while (parser->input[i])
			{
				hash_i = 0;
				if (check_syntax(&hash_i, parser->syntax, parser->input[i]))
				{
					if (is_state_active(parser->state, hash_i))
						append_stack();
				}
				i++;
			}
			return (true);
		}
	}
	return (false);
}
