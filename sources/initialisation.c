/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/12 19:51:19 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_spec[DKCT] = {VSTR, VARO, VHAS, VEXT, VHYP, VPID, VCID, VNME, VLST, VIFS};

//
bool	append_specials(t_shel **minishell)
{
	int		index;

	if (!*minishell)
		return (false);
	index = 0;
	while (index < DKCT)
	{
		(*minishell)->special[index] = strdup(g_spec[index]);
		if (!(*minishell)->special[index])
			return (false);
		index++;
	}
	return (true);
}


//
static bool build_env(t_shel **minishell, char **envp)
{
    t_env	*new;
    t_env	*tail;
    t_env	**head;

    if (*minishell)
    {
		new = NULL;
        tail = NULL;
		head = &(*minishell)->envp;
		while (*envp)
        {
        	new = create_env_node(strdup(*envp));
			if (!new)
				return (false);
            insert_env_node(head, &tail, new);
			insert_avlt_node(&(*minishell)->expt, new, strlen(new->var[KEY]));
			envp++;
		}
    }
    return (!*envp);
}

//
bool    set_env(t_shel **minishell, char **envp)
{
    if (!*minishell)
    	return (false);
    if (!build_env(minishell, envp))
    	return (false);
	else
		return (append_specials(minishell));
}
