/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 10:43:45 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	quote_removal_helper(char *token, char *removed)
{
	int		save;
	int		index;
	char	quote;

	save = 0;
	index = 0;
	quote = INIT;
	while (token[index])
	{
		if (!quote)
		{
			if (is_quote(token[index]))
				quote = token[index];
			else
				removed[save++] = token[index];
		}
		else
		{
			if (token[index] == quote)
				quote = INIT;
			else
				removed[save++] = token[index];
		}
		index++;
	}
}

//
static bool	quote_removal(t_tokn *list)
{
	int		tlen;
	char	*removed;

	while (list)
	{
		if (list->value)
		{
			tlen = strlen(list->value) + 1;
			removed = (char *)calloc(tlen, sizeof(char));
			if (!removed)
				return (false);
			quote_removal_helper(list->value, removed);
			//free(list->value);
			list->value = removed;
		}
		move_pointer(&list);
	}
	return (true);
}

//
static t_tokn	*get_execution_bloc_redirs(t_tokn **tokens, t_tokn **redirs)
{
	t_tokn	*tail;
	t_tokn	*node_redirs;

	node_redirs = create_token_sub_list(tokens, HDOC | IRED | ORED | ARED);
	tail = get_tail_node(redirs);
	if (tail)
		tail->next = node_redirs;
	else
		*redirs = node_redirs;
	return (node_redirs);
}

//
t_exec	*prepare_for_exec(t_shell **m, t_tokn *tokens, t_tokn **redirections)
{
	t_exec	*node;
	t_tokn	*deep_copy;

	deep_copy = NULL;
	if (!m || !tokens)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
    node->redirections = get_execution_bloc_redirs(&tokens, redirections);
	node->redirs[INFILE] = -1;
	node->redirs[OUTFILE] = -1;
	node->command = get_command_and_arguments(*m, tokens);
	node->environ = get_env(*m);
	node->next = NULL;
	return (node);
}
