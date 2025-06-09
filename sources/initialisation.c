/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 19:13:22 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_spec[DKCT] = {ISTR, IARO, IHAS, IEXT, IHYP, IPID, ICID, INME, ILST, IIFS};

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
	if ((index + strlen(tname))>= BUFFER_SIZE)
		return ;
	strcpy(rl_prompt, tname);
	index =+ strlen(tname);
	rl_prompt[index] = ' ';
	rl_prompt[++index] = '>';
	rl_prompt[++index] = ' ';
	rl_prompt[++index] = 0;
}

//
t_env	*append_specials(void)
{
	int		index;
	t_env	*head;
	t_env	*tail;
	char	*temp;

	index = 0;
	head = NULL;
	tail = NULL;
	while (index < DKCT)
	{
		temp = strdup(g_spec[index]);
		if (!head)
		{
			head = create_env_node(temp);
			tail = head;
		}
		else
		{
			tail->next = create_env_node(temp);
			tail = tail->next;
		}
		index++;
		free(temp);
	}
	return (head);
}


/*
bool	insert_env_in_avlt(t_shell *minishell)
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
*/
