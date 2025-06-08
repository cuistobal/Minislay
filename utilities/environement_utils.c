/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/08 15:38:51 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_keys[DKCT] = {DSTR, DARO, DHAS, DEXT, DHYP, DPID, DCID, DNME, DLST, DIFS};


void    append_exit_code(t_shell *minishell, int code, bool command)
{
    int     index;
    t_env   *node;
    char    *ecode;

    index = 3;
    if (command)
        index = 6;
    node = find_special_env_variable(minishell, index);
    if (!node)
        return ;
    ecode = ft_itoa(code);
    if (strcmp(node->var[VALUE], ecode) == 0)
        free(ecode);
    else
    {
        free(node->var[VALUE]);
        node->var[VALUE] = ecode;
    }
}

//
t_env	*find_special_env_variable(t_shell *minishell, int index)
{
	t_env	*current;

	current = minishell->special;
	if (index < 0 || index >=  DKCT)		
		return (NULL);
	while (index-- != 0)
		current = current->next;
	return (current);
}

//
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
