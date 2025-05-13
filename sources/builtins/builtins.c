/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:53:12 by ynyamets          #+#    #+#             */
/*   Updated: 2025/05/13 09:57:45 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static char	*int_to_str(int n)
{
	char	buffer[12];
	char	*res;

	snprintf(buffer, sizeof(buffer), "%d", n);
	res = strdup(buffer);
	return (res);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!strncmp(cmd, "echo", 5))
		return (1);
	if (!strncmp(cmd, "cd", 3))
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_shel *minishell)
{
	int		code;
	char	*temp;

	if (!argv || !argv[0] || !minishell)
		return (1);
	code = 1;
	if (!strncmp(argv[0], "echo", 5))
		code = builtin_echo(argv);
	if (!strncmp(argv[0], "cd", 3))
		code = cd(minishell, argv[1]);
	temp = minishell->special[DEXTI];
	minishell->special[DEXTI] = int_to_str(code);
	printf("→ DEXTI value: %s at %p\n", temp, (void *)temp);
	return (code);
}
