/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:09:46 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 15:16:34 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
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

	current = head;
	if (!new)
		return (NULL);
	if (!head)
		return (new);
	while (current->next)
		current = current->next;
	current->next = new;
	return (head);
}

//
t_exec	*handle_pipeline(t_shel **minishell, t_tree *ast)
{
	t_exec	*new;
	t_exec	*head;
	t_tokn	*modified;
	t_tokn	*redirections;

	new = NULL;
	head = NULL;
	modified = NULL;
	redirections = NULL;
	while (ast->tokens)
	{
		modified = split_token_list_if(&ast->tokens, PIPE);
		new = prepare_for_exec(minishell, ast, &redirections);
		if (!new)
		{
			free_execution_node(head);
			return (NULL);
		}
		head = insert_execution_node(head, new);	
	}
	return (head);
}
