/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/25 10:00:17 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void    trim_and_keep(t_tokn **redirections)
{
    t_tokn  *prev;
    t_tokn  *current;
    t_tokn  *last_in;
    t_tokn  *last_out;

    prev = NULL;
    last_in = NULL;
    last_out = NULL;
    current = *redirections;
    while (redirections)
    {
        if (valid_lexeme(current, HDOC, IRED))
        {
            if (last_in)
            {
                close(last_in->type);
                //free();
                //append_links;
            }
            last_in = current;
        }
        else
        {
            if (last_out)
            {
                close(last_out->type);
             //   free();
            //    append_links;
            }
            last_out = current;
        }
        prev = current;
        move_pointer(&current);
    }
}

void    open_standard_redirections(t_tokn *redirections)
{
    while (redirections)
    {
        if(!is_state_active(redirections->type, HDOC))
        {
            if(is_state_active(redirections->type, IRED))
                open_infile(redirections);
            if(is_state_active(redirections->type, ORED))
                open_outfile(redirections);
            if(is_state_active(redirections->type, ARED))
                open_outfile_append(redirections);
        }
        move_pointer(&redirections);
    }
}

void    open_here_docs(t_shell *minishell, t_tokn *redirections)
{
    while (redirections)
    {
        if (is_state_active(redirections->type, HDOC))
            handle_here_doc(minishell, redirections);
        move_pointer(&redirections);
    }
}

void	open_all_redirections(t_shell *minishell, t_exec **node)
{   
	t_exec	*current;
    t_tokn  *redirections;

    current = *node;
    while (current)
    {
        redirections = current->redirections;
        open_here_docs(minishell, redirections);
        open_standard_redirections(redirections);
        trim_and_keep(&redirections);
        current = current->next;
    }
}
