/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:25:45 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (env->var[0] && ft_strcmp(env->var[0], key) == 0)
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
	if (!target || ft_strcmp(target, "~") == 0)
		target = get_env_value(minishell->envp, "HOME");
	else if (ft_strcmp(target, "-") == 0)
	{
		target = get_env_value(minishell->envp, "OLDPWD");
		if (target)
			printf("%s\n", target);
	}
	if (!target || chdir(target) != 0)
		return (write(2, "minislay: cd: ", 14),
			write(2, args[0], ft_strlen(args[0])),
			write(2, ": No such file or directory\n", 29), BUILTINS);
	if (!getcwd(cwd, BUFFER_SIZE))
		return (BUILTINS);
	update_key_value(minishell, "OLDPWD",
		get_env_value(minishell->envp, "PWD"));
	update_key_value(minishell, "PWD", cwd);
	return (SUCCESS);
}
