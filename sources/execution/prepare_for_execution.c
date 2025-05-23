/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/23 11:57:39 by chrleroy         ###   ########.fr       */
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
static char	**initialise_execution(t_shell *minishell, t_tokn **redirections, t_tokn **expansions)
{
	int		count;
	t_tokn	*copy;

	count = 0;

	modify_token_types(expansions, redirections);

	copy = *expansions;
	if (!expand(minishell, &copy))
//	if (!expand(minishell, &copy, &count))
		return (NULL);
	if (!quote_removal(*expansions))
		return (NULL);

	//handle_redirection_list(minishell, redirections);

	return (get_command_and_arguments(minishell, *expansions));
}


//
//t_exec	*prepare_for_exec(t_shell **minishell, t_tree *ast, t_tokn **redirections)
t_exec	*prepare_for_exec(t_shell **minishell, t_tokn *tokens, t_tokn **redirections)
{
	t_exec	*node;
	t_tokn	*expansions;
	t_tokn	*assignations;

	expansions = NULL;
	assignations = NULL;
	if (!minishell || !tokens)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		return (NULL);

	split_list(tokens, &assignations, &expansions);

	node->command = initialise_execution(*minishell, redirections, &expansions);

	node->environ = NULL;
	//rebuild_env;

	node->redirections[HERE_DOC] = *redirections;
	node->redirections[INFILE] = NULL;
	node->redirections[OUTFILE] = NULL;
	node->next = NULL;
	return (node);
}
