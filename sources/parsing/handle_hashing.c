/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hashing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:38 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 09:07:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Determines the group of a character based on parser state
static int get_group(t_pars *parser, char c)
{
    int index;

	index = 0;
	while (index < GROUP_OTHER)
	{
        if (parser->check_type[index](c))
            return (index);
        index++;
    }
    return (GROUP_OTHER);
}

// Hashing function that turns user input into a group index chain
void	hash_input(t_pars *parser, int index)
{
	uint8_t	group;

	if (!is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
	{
		group = 0;
		while (index < GROUP_OTHER)
		{
	        if (parser->check_type[group](c))
				break;
        	group++;
		}
		parser->hashed[index] = group;
		return ;
	}
	parser->hashed[index] = GROUP_OTHER;
}
