/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 17:00:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Et merce arsch ;)
bool	match_pattern(char *pattern, char *current)
{
	if (*pattern == '\0' && *current == '\0')
		return (true);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, current) ||\
				(*current && match_pattern(pattern, current + 1)));
	if (*pattern == '?' || *pattern == *current)
		return (match_pattern(pattern + 1, current + 1));
	return (false);
}

