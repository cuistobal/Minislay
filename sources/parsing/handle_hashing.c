/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hashing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:38 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 16:10:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Determines the group of a character and return its group index.
static int get_group(bool (*group_functions[])(char), char c)
{
    int 	index;

    index = 0;
    while (index < GROUP_OTHER)
    {
        if (group_functions[index](c))
		{
			if (!check_status()); // Transforme index en fonction du statut du parser
            	return (GROUP_OTHER);
			return (index);
		}
		index++;
    }
    return (GROUP_OTHER);
}

//Hashing function that turns the user's input into a chain of digits rannging
//from 0 to 9 included.
//We use this array to identify tokens and construct our execution tree.
uint8_t	*handle_hashing(t_pars *parser, int index)
{
	parser->hashed[index] = get_group(check_type, user_prompt[index]);
        	    index++;
        	}
			return (input);
		}
    }
    return (NULL);
}
