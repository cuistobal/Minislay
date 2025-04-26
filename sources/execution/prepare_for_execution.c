/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:49:45 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:29:56 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	**initialise_execution(t_shel *minishell, t_tokn **redirections, t_tokn **expansions, void (*func)(void *, void *))
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

	return (get_command_and_arguments(minishell, *expansions, count, func));
}

//Entry point -> Needs some rework
//
//	Either:
//	
//		-> 	Fix the misleading name
//		->	Change the return type to char**
//
//bool	prepare_for_exec(t_shel **minishell, t_tree *ast)
char	**prepare_for_exec(t_shel **minishell, t_tree *ast, void (*func)(void *, void *))
{
	char	**command;
	t_tokn	*expansions;
	t_tokn	*redirections;
	t_tokn	*assignations;

	command = NULL;
	expansions = NULL;
	redirections = NULL;
	assignations = NULL;
	if (!*minishell && !ast)
		return (NULL);

	if (!ast->tokens)	
		return (NULL);

	split_list(ast->tokens, &assignations, &expansions);

	command = initialise_execution(*minishell, &redirections, &expansions, func);

//	print_exec(assignations, expansions, redirections, command);

//	if (!expand(*minishell, &assignations))
//		return (NULL);

//	print_tokens(assignations);

	//Identify type of command
	//
	//Turn the token list into redirs && char **exec
	return (command);
}
