/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:55:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/07 13:43:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to check if the quotes are closed.
static bool handle_quotes(t_pars *parser, char c)
{
    if (c == SQTE)
	{
        if (is_state_active(parser, STATE_SQUOT))
            unset_state(parser, STATE_SQUOT);
		else if (!is_state_active(parser, STATE_DQUOT))
            set_state(parser, STATE_SQUOT);
	}
    else if (c == DQTE)
	{
        if (is_state_active(parser, STATE_DQUOT))
            unset_state(parser, STATE_DQUOT);
		else if (!is_state_active(parser, STATE_SQUOT))
            set_state(parser, STATE_DQUOT);
	}
    return true;
}

//We use this function to check if the quotes are closed.
static bool handle_parentheses(t_pars *parser, char c)
{
    if (c == OPAR && !is_state_active(parser, STATE_SQUOT | STATE_DQUOT))
	{
        set_state(parser, STATE_SSHEL);
        push(parser, OPAR);
    }
    else if (c == CPAR && !is_state_active(parser, STATE_SQUOT | STATE_DQUOT))
	{
        if (peek(parser) == OPAR)
		{
            pop(parser);
            if (parser->top == 0)
                unset_state(parser, STATE_SSHEL);
        }
		else
            return (set_state(parser, STATE_ERROR), false);
    }
    return (true);
}

static bool handle_redirections(t_pars *parser, char c)
{
	if (c == IRDR || c == ORDR)
	{
    	if (c == IRDR)
		{
    	    if (is_state_active(parser, STATE_IREDI))
       			return (unset_state(parser, STATE_IREDI));
			else if (is_state_active(parser, STATE_OREDI))
    	        return (set_state(parser, STATE_ERROR));
    	    return (set_state(parser, STATE_IREDI));
		}
	    else if (c == ORDR)
		{
	        if (is_state_active(parser, STATE_OREDI))
	            return (unset_state(parser, STATE_OREDI));
			else if (is_state_active(parser, STATE_IREDI))
	            return (set_state(parser, STATE_ERROR));
	        return (set_state(parser, STATE_OREDI));
		}
	}
	return (unset_state(parser, STATE_OREDI | STATE_IREDI));
}

/*
static bool handle_redirections(t_pars *parser, char *input, int index)
{
	char	assess[3];

    if (index > 1)
	{
		assess[0] = input[index - 1];
		assess[1] = input[index];
		assess[2] = input[index + 1];
        if (is_redir(assess[0]) || is_redir(assess[1]) || is_redir(assess[0]))
		{
        	if (is_redir(assess[0]) && is_redir(assess[1]))
			{
				if (assess[0] == assess[1])
				{
					if (assess[1] == IRDR)
            			return (unset_state(parser, STATE_IREDI));
					return (unset_state(parser, STATE_OREDI));
				}
				return (set_state(parser, STATE_ERROR));
			}
			else if (is_redir(assess[0]) && is_redir(assess[2]))
				return (set_state(parser, STATE_ERROR));
		}
	}
    return (true);
}*/

static int get_group(bool (*group_functions[])(char), char c)
{
    int 	index;

    index = 0;
    while (index < GROUP_OTHER)
    {
        if (group_functions[index](c))
			break ;
        index++;
    }
    return (index);
}

// We use this function to split the checks between quotes and parentheses
bool handle_char(t_pars *parser, char *input, int index)
{
    char	c;
    bool	quote_handled;

    if (parser && input)
    {
        c = input[index];
        parser->user[index] = c;
        if (c == SQTE || c == DQTE)
        {
        	quote_handled = handle_quotes(parser, c);
            parser->hashed[index] = GROUP_OTHER;
            return (quote_handled);
        }
        else if (is_state_active(parser, STATE_SQUOT | STATE_DQUOT))
            parser->hashed[index] = GROUP_OTHER;
        else
            parser->hashed[index] = get_group(parser->check_type, c);
        if (c == OPAR || c == CPAR)
//            return (handle_parentheses(parser, c));
			(handle_parentheses(parser, c));
//		if (c == IRDR || c == ORDR)
//			return (handle_redirections(parser, c));
//		return (true);
		return (handle_redirections(parser, c));
    }
    return (false);
}
