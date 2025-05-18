/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:09:46 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 08:16:46 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//This function splits the token list if the current node is a PIPE
t_tokn	*split_token_list_if(t_tokn **original, int split_type)
{
	t_tokn	*head;
	t_tokn	*current;

	head = *original;	
	current = head;
	while (*original)
	{	
		*original = (*original)->next;
		if (!*original || is_state_active((*original)->type, split_type))
		{
			if (*original)
				*original = (*original)->next;
			current->next = NULL;
			break ;
		}
		current = current->next;
	}
	return (head);
}

//
t_exec	*insert_execution_node(t_exec *head, t_exec *new)
{
	t_exec	*current;

	if (!new)
		return (NULL);
	else if (!head)
		return (new);
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (head);
}

//This function splits the current's branch token into a list of command 
//separated by pipes.
t_exec	*handle_pipeline(t_shell **minishell, t_tree *ast, int *count)
{
	t_exec	*new;
	t_exec	*head;
	t_tokn	*save;
	t_tokn	*modified;
	t_tokn	*redirections;

	new = NULL;
	save = NULL;
	head = NULL;
	modified = NULL;
	redirections = NULL;
	while (ast->tokens)
	{
		modified = split_token_list_if(&ast->tokens, PIPE);
		save = ast->tokens;
		ast->tokens = modified;
		new = prepare_for_exec(minishell, ast, &redirections);
		if (!new)
			return (free_execution_node(head), NULL);
		head = insert_execution_node(head, new);
		ast->tokens = save;
		(*count)++;
	}
	return (head);
}
