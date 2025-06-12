/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:27:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:25:45 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	update_existing(t_env *curr, char *new_value)
{
	char	*copy;

	if (curr->var[1] && curr->var[1] != new_value)
	{
		free(curr->var[1]);
		curr->var[1] = NULL;
	}
	if (new_value)
	{
		copy = ft_strdup(new_value);
		if (!copy)
			return (ERROR);
		curr->var[1] = copy;
	}
	return (SUCCESS);
}

int	update_key_value_fallback(t_shell *minishell, char *key, char *new_value)
{
	t_env	*curr;

	curr = malloc(sizeof(t_env));
	if (!curr)
		return (ERROR);
	curr->var[0] = ft_strdup(key);
	if (!curr->var[0])
		return (free(curr), ERROR);
	if (new_value)
	{
		curr->var[1] = ft_strdup(new_value);
		if (!curr->var[1])
			return (free(curr->var[0]), free(curr), ERROR);
	}
	else
		curr->var[1] = NULL;
	curr->next = minishell->envp;
	minishell->envp = curr;
	return (SUCCESS);
}

int	update_key_value(t_shell *minishell, char *key, char *new_value)
{
	t_env	*curr;

	if (!minishell || !key)
		return (ERROR);
	curr = minishell->envp;
	while (curr)
	{
		if (curr->var[0] && ft_strcmp(curr->var[0], key) == 0)
			return (update_existing(curr, new_value));
		curr = curr->next;
	}
	return (update_key_value_fallback(minishell, key, new_value));
}
