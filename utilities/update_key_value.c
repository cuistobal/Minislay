/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:27:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 05:46:20 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*void	update_key_value(t_shel *minishell, char *key, char *new_value)
{
	char	*value;

	find_key(minishell, &value, key);

	value = new_value;
}*/

int	update_key_value(t_shel *minishell, char *key, char *new_value)
{
	t_env	*curr;

	if (!minishell || !key)
		return (ERROR);
	curr = minishell->envp;
	while (curr)
	{
		if (curr->var[0] && strcmp(curr->var[0], key) == 0)
		{
			if (curr->var[1])
				free(curr->var[1]);
			curr->var[1] = new_value ? strdup(new_value) : NULL;
			return (SUCCESS);
		}
		curr = curr->next;
	}
	curr = malloc(sizeof(t_env));
	if (!curr)
		return (ERROR);
	curr->var[0] = strdup(key);
	curr->var[1] = new_value ? strdup(new_value) : NULL;
	curr->next = minishell->envp;
	minishell->envp = curr;
	return (SUCCESS);
}
