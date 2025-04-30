/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/30 08:09:05 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"



//
static inline bool	is_hidden_file(char *current, int i)
{
	return (i == 0 && *current == '.');
}

//
bool	match_pattern(char **patterns, char *current, int *i)
{
    size_t  plen;

	if (!patterns || !current)
		return (false);
	if (!patterns[*i])
		return (*current == '\0');
	if (strcmp(patterns[*i], "*") == 0)
	{
		if (is_hidden_file(current, *i))	
			return (false);
        else if (patterns[*i + 1])
	    	return ((*i)++ , match_pattern(patterns, current , i));
        return (true);
	}
	else
	{
        plen = strlen(patterns[*i]);
        if (plen > strlen(current))
            return (false);
        if (strncmp(patterns[*i], current, plen) == 0)
		    return ((*i)++ , match_pattern(patterns, current + plen, i));
		return (match_pattern(patterns, current + 1, i));
    }
    return (false);
}
