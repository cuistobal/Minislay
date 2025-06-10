/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:09:25 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/12 19:12:44 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};

//static bool	is_builtin(char *command)
bool is_builtin_bool(char *command)
{
	int	index;

	index = 0;
	if (!command || !*command)
		return (false);
	while (index < BCNT)
	{
		if (strcmp(command, g_b[index]) == 0)
			break ;
		index++;
	}
	return (index < BCNT);
}

//
bool	is_absolute(char *command)
{
	return (command && *command && *command == '/');
}

bool	is_executable(char *command)
{
	return (command && *command && strncmp(command, "./", 2) == 0 );
}
