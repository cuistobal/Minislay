/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:37:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 16:23:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	open_standard_redirections(t_exec *node, t_tokn *redirections)
{
	int		last_in;
	int		last_out;
	bool	valid_command;

	last_in = -1;
	last_out = -1;
	valid_command = true;
    while (redirections)
    {
		if (!check_validity_and_append_fd(redirections, &last_in, &last_out, \
					valid_command))
			valid_command = false;
/*
		if(is_state_active(redirections->type, IRED))
        {
		    redirections->type = open_infile(redirections);
            last_in = redirections->type;
        }
		else if(is_state_active(redirections->type, ORED))
        {
            redirections->type = open_outfile(redirections);
            last_out = redirections->type;
        }
		else if(is_state_active(redirections->type, ARED))
        {
            redirections->type = open_outfile_append(redirections);
            last_out = redirections->type;
        }
*/
        move_pointer(&redirections);
    }
    append_redirs_value(node, last_in, last_out);
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
			if (prev)
				close_and_unlink(&prev, &fd, redirections->type);
            handle_here_doc(minishell, redirections);
            fd = redirections->type;
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

	current = node;
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
