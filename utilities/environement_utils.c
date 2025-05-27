/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 10:43:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_keys[DKCT] = {DSTR, DARO, DHAS, DEXT, DHYP, DPID, DCID, DNME, DLST, DIFS};

//
bool	is_standard_key(t_shell *minishell, char **value, char *key)
{
	int	index;

	index = 0;
	while (index < DKCT)
	{
		if (strcmp(key, g_keys[index]) == 0)
		{
			*value = minishell->special[index];
			break ;
		}
		index++;
	}
	return (index < DKCT);
}
