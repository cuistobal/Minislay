/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 11:19:49 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to activate the new_state passed as parameter
static bool set_state(t_parser *parser, int new_state)
{
    return (parser->state |= new_state, true);
}

//We use this function to diasable the old_state passed as parameter
static bool unset_state(t_parser *parser, int old_state)
{
    return (parser->state &= ~old_state, true);
}

//We use this function to check wether the state is active or not.
static bool	is_state_active(char state, size_t check_state)
{
    return (parser->state & check_state);
}






//This function is designed to handle the parser's state. The state allows us 
//to maintain the syntx priority.
bool	check_state(t_pars *parser, int index)
{
	if (index == 0)
	{
		if (!is_state_active(parser->state, STATE_SSHEL))
			return (false);
		set_state(parser->state, STATE_SSHEL);
	}
	else
	{
		if (!is_state_active(state, index))
		{
			if (index < 3)
			{

			}
			else
				set_state(parser, STATE_SSHEL)
		}
		else
			unset_state(state, index);
	}
}
	if (index > 0 && is_state_active(state, index))
		unset_state(state, index);
	else
	{
		if (index == 0)
		{
			set_state(state, STATE_SSHEL);
			append_stack();
		}
		else
		{
			if (is_state_active(state, index))
				unset_state(state, index);
			else
			{
				if (is_state_active(state, ))
			}
		}
	}
}
