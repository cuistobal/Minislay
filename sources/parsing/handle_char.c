/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:55:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 09:59:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to check if the quotes are closed.
static bool handle_quotes(t_parser *parser, char c)
{
    if (c == SQTE)
	{
        if (is_state_active(parser, STATE_SINGLE_QUOTE))
            unset_state(parser, STATE_SINGLE_QUOTE);
		else if (!is_state_active(parser, STATE_DOUBLE_QUOTE))
            set_state(parser, STATE_SINGLE_QUOTE);
	}
    else if (c == DQTE)
	{
        if (is_state_active(parser, STATE_DOUBLE_QUOTE))
            unset_state(parser, STATE_DOUBLE_QUOTE);
		else if (!is_state_active(parser, STATE_SINGLE_QUOTE))
            set_state(parser, STATE_DOUBLE_QUOTE);
	}
    return true;
}

//We use this function to check if the quotes are closed.
static bool handle_parentheses(t_parser *parser, char c)
{
    if (c == OPAR && !is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
	{
        set_state(parser, STATE_SUBSHELL);
        push(parser, OPAR);
    }
    else if (c == CPAR && !is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
	{
        if (peek(parser) == OPAR)
		{
            pop(parser);
            if (parser->top == 0)
                unset_state(parser, STATE_SUBSHELL);
        }
		else
            return (set_state(parser, STATE_ERROR), false);
    }
    return (true);
}

//We use this function to split the checks between quotes and parenthesis
bool	handle_char(t_parser *parser, char *input, int index)
{
    char c; 

	if (parser && input)
	{
		c = input[index];
    	parser->user[index] = c;
    	if (is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
        	parser->hashed[index] = GROUP_OTHER;
    	else
			parser->hashed[index] = get_group(parser->check_type, c);
    	if (c == SQTE || c == DQTE)
        	return (handle_quotes(parser, c));
    	if (c == OPAR || c == CPAR)
        	return (handle_parentheses(parser, c));
    	return (true);
	}
	return (false);
}
