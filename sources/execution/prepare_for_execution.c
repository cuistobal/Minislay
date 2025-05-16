/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 15:16:56 by chrleroy         ###   ########.fr       */
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
			//memset(removed, 0, tlen);
			quote_removal_helper(list->value, removed);
			free(list->value);
			list->value = removed;
		}
		move_pointer(&list);
	}
	return (true);
}

//
static char	**initialise_execution(t_shel *minishell, t_tokn **redirections, t_tokn **expansions)
{
	int		count;
	t_tokn	*copy;

	count = 0;
	modify_token_types(expansions, redirections, &count);
	copy = *expansions;
	//Inserer la modification de count pour le globing
	if (!expand(minishell, &copy, &count))
		return (NULL);
	if (!quote_removal(*expansions))
		return (NULL);
	handle_redirection_list(minishell, redirections);
	return (get_command_and_arguments(minishell, *expansions, count));
}

//
t_exec	*prepare_for_exec(t_shel **minishell, t_tree *ast, t_tokn **redirections)
{
	t_exec	*node;
	t_tokn	*expansions;
	t_tokn	*assignations;

	expansions = NULL;
	assignations = NULL;
	if (!minishell || !ast)
		return (NULL);
	if (!ast->tokens)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	split_list(ast->tokens, &assignations, &expansions);
	node->command = initialise_execution(*minishell, redirections, &expansions);

	/*
	 *	Do we treat basic assignations (ex: abc=def) ?
	 *	If so, we need to handle their expansion && assignation here
	 *
	 */

	return (node);
}
