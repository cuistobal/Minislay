/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:25:02 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 14:31:07 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	append_prompt(char **prompt, t_tokn **current)
{
	char	*joined;

	joined = NULL;
	if (current)
	{
		joined = ft_strjoin(*prompt, (*current)->value);
		if (joined)
		{
			free((*current)->value);
			(*current)->value = NULL;
			free(*prompt);
			*prompt = joined;
			joined = ft_strjoin(*prompt, " ");
			if (joined)
			{
				free(*prompt);
				*prompt = joined;
				return (true);
			}
		}
	}
	return (free(joined), free(*prompt), *prompt = NULL, false);
}

//We use this function to turn the subshell part of the list into a string.
//Hence, we can eprform recursive call to minishell.
static bool	build_prompt(char **prompt, t_tree *branch)
{
	bool	closing;
	t_tokn	*current;

	closing = false;
	if (!branch)
		return (false);
	current = branch->tokens;
	while (current)
	{
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
//		t_tokn *prev = current;
		current = current->next;
		if (!current)
			break ;
		if (current->type != CPAR)
		{
			if (!append_prompt(prompt, &current))
				return (false);
		}
		else if (!closing)
			closing = true;
		else if (!append_prompt(prompt, &current))
			return (false);
//		free(prev);
	}
	if (branch->left && !build_prompt(prompt, branch->left))
		return (false);
	if (branch->right && !build_prompt(prompt, branch->left))
		return (false);
	return (true);
}

static void	subshell_cleanup(t_tree **save)
{
	if (!*save)
		return ;
	if ((*save)->tokens)
		free_tokens_adress(&(*save)->tokens);
	(*save)->tokens = NULL;
	subshell_cleanup(&(*save)->left);
	(*save)->left = NULL;
	subshell_cleanup(&(*save)->right);
	(*save)->right = NULL;
	free(*save);
	*save = NULL;
}


//
int	handle_subshell(t_shell *minishell, t_tree *ast)
{
	int		ret;
	pid_t	pid;
	t_tree	*save;
	t_exec	*nodes;
	char	*subshell_command;

	save = minishell->ast;
	nodes = minishell->execution;
	free_execution_node(nodes);
	subshell_command = NULL;
	if (!build_prompt(&subshell_command, ast))
		return (GENERAL_ERROR);
	pid = fork();
	if (pid < 0)
		return (free(subshell_command), GENERAL_ERROR);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ret = get_minishelled(&minishell, subshell_command);
		subshell_cleanup(&save);
		free(subshell_command);
		free_minishell(minishell);
		exit(ret);
	}
	return (free(subshell_command), waitpid(pid, &ret, 0), WEXITSTATUS(ret));
}
