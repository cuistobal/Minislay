/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:42:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/25 14:39:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to append the flagged state to the parser's state.
bool	set_state(int *state, int flag)
{
	return (*state |= flag, flag != STATE_ERROR);
}

//We use this function to remove the flagged state from the parser's state.
bool	unset_state(int *state, int flag)
{
	return (*state &= ~flag, true);
}

//We use this function to check if the parser's state matches thee flagged
//state.
bool	is_state_active(int state, int flag)
{
	return (state & flag);
}
