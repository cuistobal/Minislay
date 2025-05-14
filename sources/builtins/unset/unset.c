/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 05:11:37 by ynyamets          #+#    #+#             */
/*   Updated: 2025/05/14 05:12:00 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	is_valid_key(const char *s)
{
	int	i;

	if (!s || !*s || (s[0] != '_' && (s[0] < 'A' || s[0] > 'Z')
		&& (s[0] < 'a' || s[0] > 'z')))
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != '_' && (s[i] < 'A' || s[i] > 'Z')
			&& (s[i] < 'a' || s[i] > 'z')
			&& (s[i] < '0' || s[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_from_env(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (curr->var[0] && strcmp(curr->var[0], key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->var[0]);
			free(curr->var[1]);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	unset(t_shel *minishell, char **args)
{
	int	i;

	if (!minishell || !args)
		return (ERROR);
	i = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			remove_from_env(&minishell->envp, args[i]);
		i++;
	}
	return (SUCCESS);
}
