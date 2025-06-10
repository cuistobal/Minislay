/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:12:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 08:52:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static const char *g_spec[DKCT] = {ISTR, IARO, IHAS, IEXT, IHYP, IPID, ICID, INME, ILST, IIFS};

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

//
t_env	*build_environement(char **envp)
{
	t_env	*tail;
	t_env	*head;

	head = NULL;
	while (*envp)
	{	
		if (!head)
		{
			head = create_env_node(*envp);
			if (!head)
				return (NULL);
			tail = head;
		}
		else
		{
			tail->next = create_env_node(*envp);
			if (!tail->next)
				return (NULL);
			tail = tail->next;
		}
		envp++;
	}
	return (head);
}

//
bool	build_env(t_shell **minishell, char **envp)
{
	int		index;
	t_env	*head;

	index = 0;
	if (!*minishell)
		return (false);
	(*minishell)->envp = build_environement(envp);
	if (!(*minishell)->envp)
		return (NULL);
	(*minishell)->local = NULL;
	(*minishell)->command = NULL;
	(*minishell)->special = append_specials();
	return (true);
}
