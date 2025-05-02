/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/02 10:38:37 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_spec[DKCT] = {VSTR, VARO, VHAS, VEXT, VHYP, VPID, VCID, VNME, VLST, VIFS};

//
static bool	append_specials(t_shel **minishell)
{
	int		index;
	char	*element;

	if (*minishell)
	{
		index = 0;
		while (index < DKCT)
		{
			element = strdup(g_spec[index]);
			if (!element)
				break ;
			(*minishell)->special[index] = element;
			index++;
		}
		(*minishell)->special[index] = NULL;
	}
	return (index == DKCT);
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
