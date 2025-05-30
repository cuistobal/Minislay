/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:56:37 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 08:26:09 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"
//
static bool	join_env(char **joined, char *temp[2])
{
	char	*t;
	char	*merged;

	merged = ft_strjoin(strdup(temp[0]), strdup("\""));
	if (!merged)
		return (free(merged), merged = NULL, false);
	t = ft_strjoin(merged, strdup(temp[1]));
	if (!t)
		return (free(merged), merged = NULL, free(t), t = NULL, false);
	free(merged);
	return (*joined = t, true);
}

// Had to declare a current pointer bc the original minishel pointer is moved
// for some reason.
char	**get_env(t_shell *minishell)
{
	int		size;
	int		index;
	char	**env;
	char	*temp[2];
	t_env	*current;

	index = 0;
	size = TAB_SIZE;
	current = minishell->envp;
	env = (char **)malloc(sizeof(char *) * size);
	if (!env)
		return (NULL);
	reset_array(env, 0, size);
	while (current)
	{
		reset_array(temp, 0, 2);
		if (index == size - 1)
			env = (char **)resize_array(env, sizeof(char *), &size);
		if (!env)
			return (NULL);
		temp[0] = current->var[0];
		temp[1] = current->var[1];
		if (!join_env(&env[index++], temp))
			return (free_array(env, size), NULL);
		current = current->next;
	}
	return (env);
}
