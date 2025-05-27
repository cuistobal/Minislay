/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:16:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 15:08:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	setup_redirections_in_child(t_shell **minishell, t_exec *node, int pipe[][2], int cmd)
{	
	if (cmd > 0)
	{
		dup2(pipe[cmd - 1][1], STDIN_FILENO);
		close(pipe[cmd][1]);
		close(pipe[cmd - 1][0]);
		close(pipe[cmd - 1][1]);
	}
	else
	{
		dup2(STDIN_FILENO, pipe[cmd][0]);
		close(pipe[cmd][0]);
	}
/*
	else if ((node)->next)
	{
		dup2(STDOUT_FILENO, pipe[cmd][0]);
//		dup2(pipe[cmd][0], STDOUT_FILENO);
	//	close(pipe[cmd][0]);
        close(pipe[cmd][1]);
	}
*/
	return (SUCCESS);
}
