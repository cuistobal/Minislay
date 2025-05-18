/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:53:12 by ynyamets          #+#    #+#             */
/*   Updated: 2025/05/18 14:11:34 by chrleroy         ###   ########.fr       */
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
	if (!strncmp(cmd, "env", 4))
		return (1);
	if (!strncmp(cmd, "pwd", 4))
		return (1);
	if (!strncmp(cmd, "exit", 5))
		return (1);
	if (!strncmp(cmd, "unset", 6))
		return (1);
	if (!strncmp(cmd, "export", 7))
		return (1);
	return (0);
}

void	free_env(char **env)
{
	int	index;

	index = 0;
	if (!env || !*env)
		return ;
	while (env[index])
	{
		free(env[index]);
		env[index] = NULL;
		index++;
	}
	free(env);
	env = NULL;
}

//Il faut passser en t_shell **minishell pour que les modfis soient permanentes
int	exec_builtin(char **argv, char **envp, t_shell *minishell)
{
	int		code;
	char	*temp;

	
	if (!argv || !argv[0] || !minishell)
		return (1);
	code = 1;
	if (!strncmp(argv[0], "echo", 5))
		code = builtin_echo(argv);
	else if (!strncmp(argv[0], "cd", 3))
		code = cd(minishell, argv + 1);
	else if (!strncmp(argv[0], "env", 4))
		code = env(minishell, argv + 1);
	else if (!strncmp(argv[0], "pwd", 4))
		code = pwd(minishell);
	else if (!strncmp(argv[0], "exit", 5))
		code = my_exit(minishell, argv + 1);
	else if (!strncmp(argv[0], "export", 7))
		code = export(minishell, argv + 1);
	else if (!strncmp(argv[0], "unset", 6))
		code = unset(minishell, argv + 1);
	temp = minishell->special[DEXTI];
	minishell->special[DEXTI] = int_to_str(code);
	return (code);
}
