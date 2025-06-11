/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:13:28 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 16:27:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	append_redirs_value(t_exec *node, int last_in, int last_out)
{
	if (node->redirs[INFILE] == -1)
		node->redirs[INFILE] = last_in;
	node->redirs[OUTFILE] = last_out;
}

//Used to unlink unneccessary heredocs.
//For example, in:
//
//	<< eof << bad cat
//
//	<<eof would get unlink() because it's not the last in redirection of the 
//	command bloc
void	close_and_unlink(t_tokn **heredoc, int *fd, int newfd)
{
	close((*heredoc)->type);
	unlink((*heredoc)->value);
	*heredoc = NULL;
	*fd = newfd;
}

//
bool	check_validity_and_append_fd(t_tokn *redirections, int *last_in, \
		int *last_out, bool valid_command)
{
	if (!valid_command)
		redirections->type = -1;
	else if (is_state_active(redirections->type, IRED))
    {
		redirections->type = open_infile(redirections);
        *last_in = redirections->type;
    }
	else if(is_state_active(redirections->type, ORED))
    {
		redirections->type = open_outfile(redirections);
		*last_out = redirections->type;
	}
	else if(is_state_active(redirections->type, ARED))
	{
		redirections->type = open_outfile_append(redirections);
		*last_out = redirections->type;
	}
	return ((*last_in >= -1) && *last_out >= -1);
}
