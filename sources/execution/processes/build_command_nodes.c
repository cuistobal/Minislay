/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:09:46 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/23 11:56:40 by chrleroy         ###   ########.fr       */
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

/*
static t_exec	*create_execution_node()
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->command = NULL;
	new->environ  = NULL;
	new->next = NULL;
	return (new);
}
*/

void	modify_redirections_list(t_tokn **redirs)
{
	t_tokn	*copy;
	t_tokn	*dummy;
	t_tokn	*tail;

	tail = NULL;
	copy = *redirs;
	dummy = malloc(sizeof(t_tokn));
	if (!dummy)
		return ;
	//undefined behaviour
	dummy->value = strdup("dummy");
	dummy->type	= INIT;
	dummy->next = NULL;
	while (copy)
	{
		tail = copy;	
		move_pointer(&copy);	
	}
	append_token_list(redirs, &tail, dummy);
}

//This function splits the current's branch token into a list of command 
//separated by pipes.
//t_exec	*build_command_node(t_shell **minishell, t_tree *ast)
t_exec	*build_command_node(t_shell **minishell, t_tokn	*tokens, t_tokn **redirs)
{
	t_exec	*new;
	t_exec	*head;
	t_exec	*tail;
	t_tokn	*save;
	t_tokn	*modified;

	new = NULL;
	save = NULL;
	head = NULL;
	tail = NULL;
	modified = NULL;
	while (tokens)
	{
		modified = split_token_list_if(&tokens, PIPE);
		save = tokens;
		tokens = modified;
		new = prepare_for_exec(minishell, tokens, redirs);
		if (!new)
			return (free_execution_node(head), NULL);
		append_exec_list(&head, &tail, new);
		modify_redirections_list(redirs);
		tokens = save;
	}
	return (head);
}
