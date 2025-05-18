/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 12:05:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **envp)
{
	if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(command, 0);
		exit(GENERAL_ERROR);
	}
	return (SUCCESS);
}

//This function handles redirections
static int	setup_redirections_in_child(int pipefd[][2], int command, int count)
{

	//test version
	if (command > 0)
	{
		dup2(pipefd[command - 1][0], STDIN_FILENO);
		close(pipefd[command - 1][1]);
	}
	if (command < count - 1)
	{
		dup2(pipefd[command][1], STDOUT_FILENO);
        close(pipefd[command][0]);
	}

/*
	//if there is an input redirection
	if ((*node)->redirections[INFILE] != STDIN_FILENO)
	{
		if (dup2((*node)->redirections[INFILE], STDIN_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close((*node)->redirections[INFILE]);
	}

	//if there is an out redirection
	if ((*node)->redirections[OUTFILE] != STDOUT_FILENO)
	{
		if (dup2((*node)->redirections[OUTFILE], STDOUT_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close((*node)->redirections[OUTFILE]);
	}
	else if ((*node)->next)
	{
		//redirect command in pipe
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close(pipefd[1]);
	}
	close(pipefd[0]);
	return (SUCCESS);
*/
}

//
static void	close_unused_pipes(t_exec **node, int pipefd[2])
{
	if (!(*node)->next)
		return ;
	close(pipefd[1]);
	if ((*node)->redirections[INFILE] == STDIN_FILENO)
		(*node)->redirections[INFILE] = pipefd[0];
}

//
pid_t	create_and_execute_child(t_exec **node, int pipefd[][2], int index, int count)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	else if (child == 0)
	{
		setup_redirections_in_child(pipefd, index, count);
		execute_command_in_child((*node)->command, (*node)->environ);
	}
	return (child);
}

//
int	execute_commands(t_shell **minishell, t_exec *node, int *count)
{
	int		index;
	t_exec	*current;
	pid_t	pids[BUFFER_SIZE];
	int		pipefd[BUFFER_SIZE][2];


	//Introduce the difference between pipelines and simple commands here



	if (*count >= BUFFER_SIZE)
		return printf("Malveillance max\n");

	index = 0;
	current = node;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd[index]) < 0)
				return (GENERAL_ERROR);
		}
		pids[index] = create_and_execute_child(&current, pipefd, index, *count);
		if (pids[index] < 0)
			return (GENERAL_ERROR);
		close_unused_pipes(&current, pipefd[index]);
		current = current->next;
		index++;
	}
	return (wait_module(pids, *count));
	//return (wait_module(node));
}
