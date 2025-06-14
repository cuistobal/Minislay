/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:25:02 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 19:02:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	append_prompt(char **prompt, t_tokn **current)
{
	char	*joined;

	joined = NULL;
	if (*current)
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
				return (free(*prompt), *prompt = joined, true);
		}
	}
	return (free(joined), free(*prompt), *prompt = NULL, false);
}

static bool	handle_pointer(t_tokn **current)
{
	if (*current && (*current)->value)
	{
		free((*current)->value);
		(*current)->value = NULL;
	}
	move_pointer(current);
	return (*current);
}
/*
static bool	handle_loop(t_tokn **current, char **prompt, bool *closing)
{
	if ((*current)->type != CPAR)
	{
		if (!append_prompt(prompt, current))
			return (false);
	}
	else if (!*closing)
		*closing = true;
	else if (!append_prompt(prompt, current))
		return (false);
	return (true);
}
*/

//We use this function to turn the subshell part of the list into a string.
//Hence, we can eprform recursive call to minishell.
bool	build_prompt(char **prompt, t_tree *branch)
{
	bool	closing;
	t_tokn	*current;

	closing = false;
	if (!branch)
		return (false);
	current = branch->tokens;
	while (current)
	{
		if (!handle_pointer(&current))
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
	}
	return (build_prompt_helper(prompt, branch));
}

//
int	handle_subshell(t_shell *minishell, t_tree *ast)
{
	int		ret;
	pid_t	pid;
	t_tree	*save;
	char	*subshell_command;

	save = minishell->ast;
	subshell_command = NULL;
	if (!build_prompt(&subshell_command, ast))
		return (GENERAL_ERROR);
	pid = fork();
	if (pid < 0)
		return (free(subshell_command), GENERAL_ERROR);
	if (pid == 0)
	{
		purge_tree(&save);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ret = get_minishelled(&minishell, subshell_command);
		free(subshell_command);
		free_minishell(minishell);
		exit(ret);
	}		
	return (free(subshell_command), waitpid(pid, &ret, 0), WEXITSTATUS(ret));
}
