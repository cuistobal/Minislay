/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:42:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 11:21:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to append the flagged state to the parser's state.
bool	set_state(t_parser *parser, int flag)
{
	return (parser->state |= flag, true):
}

//We use this function to remove the flagged state from the parser's state.
bool	unset_state(t_parser *parser, int flag)
{
	return (parser->state &= ~flag, true);
}

//We use this function to check if the parser's state matches thee flagged
//state.
bool	is_state_active(t_parser *parser, int flag)
{
	return (parser->state & flag);
}
