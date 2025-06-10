/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 14:53:47 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static inline bool	is_hidden_file(char *current, int i)
{
	return (i == 0 && *current == '.');
}
//
bool	match_pattern(char **patterns, char *current, int *i)
{
	char	*temp;

	if (!patterns || !current)
		return (false);
	temp = NULL;
	if (!patterns[*i])
		return (true);
	if	(strcmp(patterns[*i], "*") == 0)
	{
		if (is_hidden_file(current, *i))	
			return (false);
		return ((*i)++, match_pattern(patterns, current, i));
	}
	else
	{
		temp = strstr(current, patterns[*i]);
		if (temp && *temp == *current)
			return ((*i)++, match_pattern(patterns, temp + strlen(temp), i));
		return (false);
	}
	return (true);
}
