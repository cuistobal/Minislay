/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:16:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 11:46:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	setup_redirections_in_child(t_shell **minishell, t_exec *node, int pipe[][2], int cmd)
{	
	if (cmd > 0)
	{
		dup2(pipe[cmd - 1][0], STDIN_FILENO);
		close(pipe[cmd - 1][0]);
		close(pipe[cmd - 1][1]);
	}
	else if ((node)->next)
	{
		dup2(pipe[cmd][1], STDOUT_FILENO);
	//	close(pipe[cmd][0]);
        close(pipe[cmd][1]);
	}
	return (SUCCESS);
}
