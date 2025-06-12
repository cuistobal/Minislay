/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:13:53 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Réimplémentation de ft_strtok_r
char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*token_start;

	if (str == NULL)
		str = *saveptr;
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		str++;
	}
	*saveptr = str;
	return (token_start);
}
