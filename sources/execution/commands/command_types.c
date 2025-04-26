/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:09:25 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:42:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};
static const void *g_f[BCNT] = {cd, pwd, env, echo, my_exit, unset, export};

//static bool	is_builtin(char *command)
bool is_builtin(char *command, void (*func)(void *, void *))
{
	int	index;

	index = 0;
	if (!command || !*command)
		return (false);
	while (index < BCNT)
	{
		if (strcmp(command, g_b[index]) == 0)
		{
			func = g_f[index];
			break;
		}
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
