/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:09:34 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 15:39:27 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to create a new tree_node
t_tree	*create_tree_node(t_tokn *tokens)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->tokens = tokens;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

//
static bool	build_ast_helper(t_pars **parser, t_tokn *save, t_tree *branch)
{
	if (parse_script(parser))
		return (reset_parser(*parser, save, TTHEAD, &branch->right), \
				parse_script(parser));
	return (false);
}

//
bool	build_ast(t_pars **parser)
{
	t_tokn	*save;
	t_tree	*branch;

	branch = NULL;
	if (!*((*parser)->ast))
		*((*parser)->ast) = create_tree_node(NULL);
	if (*((*parser)->ast))
	{
		branch = *((*parser)->ast);
		delete_links(*parser);
		save = (*parser)->tab[TTNEXT];
		if ((*parser)->tab[TTCURR] && \
				valid_lexeme((*parser)->tab[TTCURR], PIPE, LORR))
		{
			branch->tokens = (*parser)->tab[TTCURR];
			reset_parser(*parser, (*parser)->tab[TTHEAD], \
					TTHEAD, &branch->left);
			return (build_ast_helper(parser, save, branch));
		}
		else if (!(*parser)->tab[TTNEXT])
			return (branch->tokens = (*parser)->tab[TTHEAD], true);
		return (false);
	}
	return (branch);
}
