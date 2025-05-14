/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:53:12 by ynyamets          #+#    #+#             */
/*   Updated: 2025/05/14 13:58:44 by chrleroy         ###   ########.fr       */
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

//int	exec_builtin(char **argv, char **envp, t_shel **minishell)
int	exec_builtin(t_shel *minishell, t_exec *execution)
{
	int		code;
	char	*temp;
	char	**argv;

	argv = (execution)->command;
	if (!argv || !argv[0] || !minishell)
		return (1);
	code = 1;
	if (!strncmp(argv[0], "echo", 5))
		code = builtin_echo(argv);
	if (!strncmp(argv[0], "cd", 3))
		code = cd(minishell, argv + 1);
	if (!strncmp(argv[0], "env", 4))
		code = env(minishell, argv + 1);
	if (!strncmp(argv[0], "pwd", 4))
		code = pwd(minishell);
	if (!strncmp(argv[0], "exit", 5))
		my_exit(minishell, execution);
	temp = (minishell)->special[DEXTI];
	(minishell)->special[DEXTI] = int_to_str(code);
	printf("→ DEXTI value: %s at %p\n", temp, (void *)temp);
	return (code);
}
