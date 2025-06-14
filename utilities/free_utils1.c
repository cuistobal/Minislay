/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 08:21:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 08:22:19 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	purge_tree(t_tree **tree)
{
	if (!*tree)
		return ;
	free_tokens_adress(&(*tree)->tokens);
	purge_tree(&(*tree)->left);
	(*tree)->left = NULL;
	purge_tree(&(*tree)->right);
	(*tree)->right = NULL;
	free(*tree);
	*tree = NULL;
}
