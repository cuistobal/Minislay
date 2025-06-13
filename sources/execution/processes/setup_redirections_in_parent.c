/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_parent.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:03:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 19:13:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	redirections_in_parent(t_exec *node, int pipe[][2], int index)
{
	if (!node->next)
		return ;
	if (index > 0)
		close(pipe[index - 1][READ_END]);
	close(pipe[index][WRITE_END]);
	if (node->redirs[INFILE] >= 0)
		close(node->redirs[INFILE]);
	if (node->redirs[OUTFILE] >= 0)
		close(node->redirs[OUTFILE]);
}
