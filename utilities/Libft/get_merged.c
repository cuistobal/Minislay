/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_merged.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:01:34 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 15:10:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to merge to arrays and free their original memory adress
bool	get_merged(char **merged, char **temp, char **expanded)
{
	*merged = ft_strjoin(*temp, *expanded);
	if (*merged)
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		*expanded = *merged;
		return (true);
	}
	else
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		free(*expanded);
		*expanded = NULL;
	}
	return (false);
}

