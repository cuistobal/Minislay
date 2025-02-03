/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/03 12:10:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to activate the new_state passed as parameter
static void set_state(t_parser *parser, int new_state)
{
    parser->state |= new_state;
}

//We use this function to diasable the old_state passed as parameter
static void unset_state(t_parser *parser, int old_state)
{
    parser->state &= ~old_state;
}

//We use this function to check wether the state is active or not.
static bool	is_state_active(char state, size_t check_state)
{
    return (parser->state & check_state);
}

//This function is designed to handle the parser's state. The state allows us 
//to maintain the syntx priority.
bool	check_state(char *state, int index)
{
	if (is_state_active(*state, index))
		unset_state(*state, index);
	else
	{

	}
}


