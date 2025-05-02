/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:42:05 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/02 10:45:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	free_avlt(t_avlt *tree)
{
	if (tree)
	{
		free_avlt(tree->left);
		free_avlt(tree->right);
		free(tree);
	}
}

void	free_env_list(t_env	*list)
{
	t_env	*prev;

	prev = list;
	while (list)
	{
		list = list->next;
		free(prev->var[KEY]);
		free(prev);
		prev = list;
	}
}

//
void	free_array(char **array, int count)
{
	if (array)
	{
		while (count--)
		{
			free(array[count]);
			array[count] = NULL;
		}
		free(array);
		array = NULL;
	}
}

//
void	free_tree(t_tree *ast)
{
	if (ast)
	{
		free_tree(ast->left);
		free_tree(ast->right);
		free_tokens(ast->tokens);
		free(ast);
	}
}
