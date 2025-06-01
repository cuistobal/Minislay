/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:09:46 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 14:19:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//This function splits the token list if the current node is a PIPE
t_tokn	*split_token_list_if(t_tokn **original, int split_type)
{
	t_tokn	*head;
	t_tokn	*prev;
	t_tokn	*current;

	head = *original;	
	current = head;
	while (*original)
	{	
		*original = (*original)->next;
		if (!*original || is_state_active((*original)->type, split_type))
		{
			if (*original)
			{
				prev = *original;
				*original = (*original)->next;
				free(prev->value);
				free(prev);
			}
			current->next = NULL;
			break ;
		}
		current = current->next;
	}
	return (head);
}

//This function splits the current's branch token into a list of command 
//separated by pipes.
//t_exec	*build_command_node(t_shell **minishell, t_tree *ast)
t_exec	*build_command_node(t_shell **minishell, t_tokn	*tokens, int *count)
{
	t_exec	*new;
	t_exec	*head;
	t_exec	*tail;
	t_tokn	*modified;

	new = NULL;
	head = NULL;
	tail = NULL;
	modified = NULL;
	while (tokens)
	{
		modified = split_token_list_if(&tokens, PIPE);
		new = prepare_for_exec(minishell, modified);
		if (!new)
			return (free_execution_node(head), NULL);
		append_exec_list(&head, &tail, new);
		(*count)++;
	}
	return (head);
}
