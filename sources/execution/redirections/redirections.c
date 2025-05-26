/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/26 09:50:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
t_tokn	*trimmed_list(t_tokn *last_in, t_tokn *last_out)
{
	t_tokn	*list;

	list = NULL;
	if (!last_in && !last_out)
		return (NULL);
	if (!last_in)
			list = create_token_node("", INIT);
	else
	{
		list = copy_token(last_in);
		if (!list)
			return (NULL);
	}
	if (last_out)
		list->next = copy_token(last_out);
	else
		list->next = NULL;
	return (list);
}

//
t_tokn	*trim_and_keep(t_tokn **redirections)
{
    t_tokn  *current;
    t_tokn  *last_in;
    t_tokn  *last_out;

    last_in = NULL;
    last_out = NULL;
    current = *redirections;
    while (current)
    {
        if (valid_lexeme(current, HDOC, IRED))
        {
            if (last_in)
                close(last_in->type);
            last_in = current;
        }
        else
        {
            if (last_out)
                close(last_out->type);
            last_out = current;
        }
        move_pointer(&current);
    }
	return (trimmed_list(last_in, last_out));
}

//
static void	open_standard_redirections(t_tokn *redirections)
{
    while (redirections)
    {
        if(!is_state_active(redirections->type, HDOC))
        {
			printf("%d	vs	", redirections->type);
            if(is_state_active(redirections->type, IRED))
                open_infile(redirections);
            if(is_state_active(redirections->type, ORED))
                open_outfile(redirections);
            if(is_state_active(redirections->type, ARED))
                open_outfile_append(redirections);
			printf("%d\n", redirections->type);
        }
        move_pointer(&redirections);
    }
}

//
static void	open_here_docs(t_shell *minishell, t_tokn *redirections)
{
    while (redirections)
    {
        if (is_state_active(redirections->type, HDOC))
            handle_here_doc(minishell, redirections);
        move_pointer(&redirections);
    }
}

//
void	open_all_redirections(t_shell *minishell, t_exec **node)
{   
	t_exec	*current;
	t_tokn	*final_list;
    t_tokn  *redirections;

	redirections = NULL;
    current = *node;
	final_list = NULL;
    while (current)
    {
        redirections = current->redirections;
        open_here_docs(minishell, redirections);
        open_standard_redirections(redirections);
        final_list = trim_and_keep(&redirections);
	//	free_tokens((*node)->redirections);
		(*node)->redirections = final_list;
        current = current->next;
    }
}
