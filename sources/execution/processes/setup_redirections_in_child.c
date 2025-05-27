/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:16:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 16:14:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
int	setup_redirections_in_child(t_shell **minishell, t_exec *node, int pipe[][2], int cmd)
{	
	close(pipe[cmd][WRITE_END]);
	if (cmd > 0)
		dup2(pipe[cmd - 1][WRITE_END], STDIN_FILENO);
	else
		dup2(STDIN_FILENO, pipe[cmd][READ_END]);
	return (SUCCESS);
}
*/

int	setup_redirections_in_child(t_shell **minishell, t_exec *node, int pipefd[][2], int index)
{

    int infile;
	int outfile;

	infile = node->redirs[INFILE];
	outfile = node->redirs[OUTFILE];

    if (infile != -1)
    {
        dup2(infile, STDIN_FILENO);
        close(infile);
    }
	else if (index > 0)
    {
        dup2(pipefd[index - 1][READ_END], STDIN_FILENO);
        close(pipefd[index - 1][READ_END]);
    }
    if (outfile != -1)
    {
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
    }
    else if (node->next)
    {
        dup2(pipefd[index][WRITE_END], STDOUT_FILENO);
        close(pipefd[index][WRITE_END]);
    }
	return (SUCCESS);
}
