/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/29 10:15:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"
//#include "globing.h"

//
bool	match_pattern(char **patterns, char *current)
{
	char	*temp;

	if (!patterns || !current)
		return (false);
	temp = NULL;
	if (*patterns)
	{
		if	(strcmp(*patterns, "*") == 0)
			return (match_pattern(patterns + 1, current));
		else
		{
			temp = strstr(current, *patterns);
			if (temp)
				return (match_pattern(patterns + 1, temp + strlen(temp)));	
		}
	}
	return (false);
}
