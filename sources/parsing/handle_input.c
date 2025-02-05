/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:04:51 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 16:21:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool handle_non_whitespace()
{
	in_whitespace = false;
	handle_char(parser, input[index]);
	parser->user[write_index++] = input[index];
}

static bool	handle_whitespaces()
{
	if (!is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
	{
		if (in_whitespace || is_whitespace(input[index + 1]))
			return (true);
		in_whitespace = true;
	}
	else
		parser->user[write_index++] = input[index];
}

bool	handle_input(t_pars *parser, char *input, int index)
{
	static int	write_index;
	static bool	in_whitespace;

	if (index == 0)
	{
		in_whitespace = true;
		write_index = 0;
	}
	if (input[index])
	{
		if (is_whitespace(input[index]))
		{
			if ()
		}
		else
		{
			handle_non_whitespace();
		}
	}
}



	if (is_whitespace(input[index]))
	{
		if (!is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
		{
			if (in_whitespace || is_whitespace(input[index + 1]))
				return (true);
			in_whitespace = true;
		}
		else
			parser->user[write_index++] = input[index];
	}
	else
	{
		in_whitespace = false;
		handle_char(parser, input[index]);
		parser->user[write_index++] = input[index];
	}
	return (true);
}
