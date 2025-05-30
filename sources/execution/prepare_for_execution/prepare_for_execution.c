/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 10:02:48 by chrleroy         ###   ########.fr       */
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
t_exec	*prepare_for_exec(t_shell **m, t_tokn *tokens)
{
	t_exec	*node;

	if (!m || !tokens)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
    node->redirections = create_token_sub_list(&tokens, HDOC | IRED | ORED | ARED);
	node->redirs[INFILE] = -1;
	node->redirs[OUTFILE] = -1;
	node->command = get_command_and_arguments(*m, tokens);
	node->environ = get_env(*m);
	node->next = NULL;
	return (node);
}
