/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:16:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 12:49:10 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"


// Il faut gerer les here_doc en amont

//
int	setup_redirections_in_child(t_shell **minishell, t_exec **node, int pipe[][2], int cmd)
{
	if ((*node)->redirections[INFILE])
	{
		handle_redirection_list(minishell, &(*node)->redirections[INFILE]);
	}
	else if (cmd > 0)
//		if (command > 0)
		//&& !(*node)->redirections[INFILE])
	{
		dup2(pipe[cmd - 1][0], STDIN_FILENO);
		close(pipe[cmd - 1][1]);
	}


	if ((*node)->redirections[OUTFILE])
		handle_redirection_list(minishell, &(*node)->redirections[OUTFILE]);
	else if ((*node)->next)
//	if (command < count - 1)
	{
		dup2(pipe[cmd][1], STDOUT_FILENO);
        close(pipe[cmd][0]);
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
*/
	return (SUCCESS);

}
