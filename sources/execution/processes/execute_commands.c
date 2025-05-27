/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 15:33:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **envp)
{
	int	code;

	if (!command || !*command || !env || !*env)
		return (GENERAL_ERROR);
	else if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(envp, 0);
		exit(GENERAL_ERROR);
	}
	return (SUCCESS);
}

/*
static void	close_unused_pipes(t_exec *node, int pipefd[2])
{
	//if ((*node)->redirections && (*node)->redirections->type != -1)
	//	close((*node)->redirections->type);	
	if (!node->next)
		return ;
//	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	//	if ((*node)->redirections && (*node)->redirections->type != -1)
	//		pipefd[0] = (*node)->redirections->type;	
}
*/

//
pid_t	create_and_execute_child(t_shell **minishell, t_exec *node, int pipefd[][2], int index)
{
	pid_t	child;
	bool	builtin;

	builtin = false;
	if (node->command);
		builtin = is_builtin(*node->command);
	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0)
	{
		//comportemment par defaut des signaux
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_redirections_in_child(minishell, node, pipefd, index);
		if (!builtin)
			execute_command_in_child((node)->command, (node)->environ);
	}
	else if (builtin)
		exec_builtin((node)->command, (node)->environ, *minishell);
	return (child);
}

//
void	redirections_in_parent(t_exec *node, int pipefd[][2], int index)
{

    if (index > 0)
        close(pipefd[index - 1][0]);
    if (node->next)
        close(pipefd[index][1]);

/*
	int	infile;
	int	outfile;

	infile = node->redirs[INFILE];
	outfile = node->redirs[OUTFILE];
	if (infile != -1)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else if (index > 0)
	{
		dup2(pipefd[index - 1][0], STDIN_FILENO);
		close(pipefd[index - 1][0]);
	}
	if (outfile != -1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
    else if (node->next)
    {
        dup2(pipefd[index][1], STDOUT_FILENO);
        close(pipefd[index][1]);
    }
*/
}

//
static void	get_or_restore_stds(int fds[2], bool set)
{
	if (set)
	{
		fds[0] = dup(STDIN_FILENO);
		fds[1] = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
	}
}

//
int	execute_commands(t_shell **minishell, t_exec *node)
{
	int				index;
	t_exec			*current;
	int				original_stds[2];
	pid_t			pids[BUFFER_SIZE];
	int				pipefd[BUFFER_SIZE][2];

	index = 0;
	current = node;
	get_or_restore_stds(original_stds, true);
	while (current)
	{
		if (current->next && pipe(pipefd[index]) < 0)
			return (GENERAL_ERROR);
		redirections_in_parent(current, pipefd, index);
		pids[index] = create_and_execute_child(minishell, current, pipefd, index);
		if (pids[index] < 0)
			return (GENERAL_ERROR);
		//close_unused_pipes(current, pipefd[index]);
		current = current->next;
		index++;
		if (index == BUFFER_SIZE)
			break ;
	}
	get_or_restore_stds(original_stds, false);
	if (index == BUFFER_SIZE)
			return (free_execution_node(node), GENERAL_ERROR);
	return (wait_module(pids, index));
}
