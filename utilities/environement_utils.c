/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 08:24:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char	*g_keys[DKCT] = {
	DSTR, DARO, DHAS, DEXT, DHYP,
	DPID, DCID, DNME, DLST, DIFS
};

void	append_exit_code(t_shell *minishell, int code)
{
	t_env	*node;
	char	*ecode;

	node = find_special_env_variable(minishell, EXT_INDEX);
	if (!node)
		return ;
	if (is_state_active(code, EXIT_MASK))
		unset_state(&code, EXIT_MASK);
	ecode = ft_itoa(code);
	if (!ecode)
		return ;
	if (!node->var[VALUE])
		node->var[VALUE] = ecode;
	else if (!*node->var[VALUE])
	{
		free(node->var[VALUE]);
		node->var[VALUE] = ecode;
	}	
	else if (strcmp(node->var[VALUE], ecode) == 0)
		free(ecode);
	else
	{
		free(node->var[VALUE]);
		node->var[VALUE] = ecode;
	}
}

t_env	*find_special_env_variable(t_shell *minishell, int index)
{
	t_env	*current;

	current = minishell->special;
	if (index < 0 || index >= DKCT)
		return (NULL);
	while (index-- != 0)
		current = current->next;
	return (current);
}

bool	is_standard_key(t_shell *minishell, char **value, char *key)
{
	int		index;
	t_env	*current;

	index = 0;
	current = minishell->special;
	while (index < DKCT)
	{
		if (strcmp(current->var[KEY], key) == 0)
		{
			*value = current->var[VALUE];
			break ;
		}
		index++;
		current = current->next;
	}
	return (index < DKCT);
}
