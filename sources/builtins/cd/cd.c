/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 11:07:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (env->var[0] && strcmp(env->var[0], key) == 0)
			return (env->var[1]);
		env = env->next;
	}
	return (NULL);
}

int	cd(t_shell *minishell, char **args)
{
	char	cwd[BUFFER_SIZE];
	char	*target;

	if (!minishell || !args)
		return (write(2, "minislay: cd: too many arguments\n", 33), ERROR);
	target = args[0];
	if (!target || strcmp(target, "~") == 0)
		target = get_env_value(minishell->envp, "HOME");
	else if (strcmp(target, "-") == 0)
	{
		target = get_env_value(minishell->envp, "OLDPWD");
		if (target)
		{
			write(1, target, strlen(target));
			write(1, "\n", 1);
		}
	}
	if (!target || chdir(target) != 0)
		return (write(2, "minislay: cd: ", 14),
			write(2, args[0], strlen(args[0])),
			write(2, ": No such file or directory\n", 29), ERROR);
	if (!getcwd(cwd, BUFFER_SIZE))
		return (ERROR);
	update_key_value(minishell, "OLDPWD",
		get_env_value(minishell->envp, "PWD"));
	update_key_value(minishell, "PWD", cwd);
	return (SUCCESS);
}
