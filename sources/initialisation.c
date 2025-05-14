/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 17:50:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_spec[DKCT] = {VSTR, VARO, VHAS, VEXT, VHYP, VPID, VCID, VNME, VLST, VIFS};

//
void	build_rl_prompt(char *rl_prompt, char *tname)
{
	int	index;

	index = 0;
	if (*tname == '.')
	{
		tname++;
		tname++;
		index = -2;
	}
	strcpy(rl_prompt, tname);
	index =+ strlen(tname);
	rl_prompt[index] = ' ';
	rl_prompt[++index] = '>';
	rl_prompt[++index] = 0;
}

//
static bool	append_specials(t_shel **minishell)
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
bool	insert_env_in_avlt(t_shel *minishell)
{
	t_env	*copy;
	t_avlt	*root;

	root = minishell->expt;
	copy = minishell->envp;
	while(copy)
	{
		insert_avlt_node(&root, copy, strlen(copy->var[KEY]));
		copy = copy->next;
	}
	return (!copy);
}

/*
t_env	*build_environement(char **envp)
{
    t_env	*new;
    t_env	*tail;
    t_env	*head;

	head = NULL;
	while (*envp)
	{	
		if (!head)
		{
			new = create_env_node(&head, strdup(*envp));
			if (!new)
				return (false);
			tail = head;
		}
		else
		{
			new = create_env_node(&tail, strdup(*envp));
			if (!new)
				return (false);
		}
		envp++;
	}
	return (head);	
}

//
bool	build_env(t_shel **minishell, char **envp)
{
    t_env	*head;
	t_avlt	*root;

    if (!*minishell)
		return (false);
	root = NULL;
	(*minishell)->envp = build_environement(envp);
	head = (*minishell)->envp;
	while (head)
	{
		insert_avlt_node(&root, head, strlen(head->var[KEY]));
		head = head->next;
	}
	(*minishell)->expt = root;
	append_specials(minishell);	
	return (true);
}
*/
