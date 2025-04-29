/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/29 11:34:53 by chrleroy         ###   ########.fr       */
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
	char	*temp;

	if (!patterns || !current)
		return (false);
	temp = NULL;
	if (!patterns[*i])
		return (*current == '\0');

	if	(strcmp(patterns[*i], "*") == 0)
	{
		if (is_hidden_file(current, *i))	
			return (false);
		return ((*i)++, match_pattern(patterns, current, i));
	}
	if (strcmp(patterns[*i], "*") != 0)
	{
		temp = strstr(current, patterns[*i]);
		if (temp && *temp == *current)	
			return ((*i)++, match_pattern(patterns, temp + strlen(temp), i));
		else if (*i > 0 && strcmp(patterns[*i - 1], "*") == 0)
			return ((*i)--, match_pattern(patterns, current + 1 , i));
		return (false);
	}
	return (true);
}
