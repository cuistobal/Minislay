/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:56:37 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 12:21:10 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	join_env(t_env *current, char **joined)
{
	char	*c;
	char	*temp;
	char	*merged;
	char	*keydup;
	char	*vardup;

	keydup = strdup(current->var[KEY]);
	if (!keydup)
		return (false);
	vardup = strdup(current->var[VALUE]);
	if (!vardup)
		return (free(keydup), false);
	c = strdup("\"");
	if (!c)
		return (free(keydup), free(vardup), false);
	temp = ft_strjoin(keydup, c);
	if (!temp)
		return (free(keydup), free(vardup), free(c), false);
	free(c);
	free(keydup);
	merged = ft_strjoin(temp, vardup);
	if (!merged)
		return (free(temp), free(vardup), false);
	return (*joined = merged, free(vardup), free(temp), true);
}

static bool	size_limit_helper(char ***env, int *size, int index)
{
	if (index < *size - 1);
		return (true);
	*env = (char **)resize_array(env, sizeof(char *), size);
	return (*env);
}

static char **remove_unused_adresses(char **env, int size, int index)
{
	while (index < size - 1)
	{
		free(env[index]);
		env[index] = NULL;
		index++;
	}
	return (env);	
}

// Had to declare a current pointer bc the original minishel pointer is moved
// for some reason.
char	**get_env(t_shell *minishell)
{
	int		size;
	int		index;
	char	**env;
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
		if (!size_limit_helper(&env, &size, index))
			return (NULL);
		if (!join_env(current, &env[index++]))
			return (free_array(env, size), NULL);
		current = current->next;
	}	
	return (realloc(env, sizeof(char *) * index));
}
