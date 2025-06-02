/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:37:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 14:09:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	open_standard_redirections(t_exec *node, t_tokn *redirections)
{
	int	last_in;
	int	last_out;

	last_in = -1;
	last_out = -1;
    while (redirections)
    {
		if(is_state_active(redirections->type, IRED))
			last_in = open_infile(redirections);
		else if(is_state_active(redirections->type, ORED))
			last_out = open_outfile(redirections);
		else if(is_state_active(redirections->type, ARED))
			last_out = open_outfile_append(redirections);
        move_pointer(&redirections);
    }
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
static void	close_and_unlink(t_tokn **heredoc, int *fd, int newfd)
{
	close((*heredoc)->type);
	unlink((*heredoc)->value);
	*heredoc = NULL;
	*fd = newfd;
}

//
static int	open_here_docs(t_shell *minishell, t_tokn *redirections)
{
	int		fd;
	t_tokn	*prev;

	fd = -1;
	prev = NULL;
    while (redirections)
    {
		if (is_state_active(redirections->type, IRED) && fd != -1)
			close_and_unlink(&prev, &fd, -1);
		else if (is_state_active(redirections->type, HDOC))
		{
            //handle_here_doc(minishell, redirections);
			if (prev)
				close_and_unlink(&prev, &fd, redirections->type);
            handle_here_doc(minishell, redirections);
			prev = redirections;
		}
        move_pointer(&redirections);
    }
	return (fd);
}

//
void	open_all_redirections(t_shell *minishell, t_exec *node)
{   
	t_exec	*current;
    t_tokn  *redirections;

	current =node;
	redirections = NULL;
    while (current)
    {
        redirections = current->redirections;
		if (redirections)
		{
			current->redirs[INFILE] =  open_here_docs(minishell, redirections);
    	    open_standard_redirections(current, redirections);
		}
        current = current->next;
    }
}
