/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:21:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:21:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	free_avlt_tree(t_avlt *root)
{
	if (root)
	{
		free_avlt_tree(root->left);
		free_avlt_tree(root->right);
		free(root);
	}
}

/*
//This function takes the adress of a t_avlt pointer and allocates & intialize
//its memory if it's NULL.
bool	create_avlt_node(t_avlt **new, char *key, char *value)
{
	if (!*new)
	{
		*new = (t_avlt *)malloc(sizeof(t_avlt));
		if (*new)
		{
			(*new)->height = 1;
			(*new)->left = NULL;
			(*new)->right = NULL;
			(*new)->data[0] = strdup(key);
			if ((*new)->data[0])
			{
				(*new)->data[1] = strdup(value);
				if (!(*new)->data[1])
					return ((*new)->data[1]);
			}
			return ((*new)->data[0]);
		}
	}
	return (*new);
}

//
bool	insert_node(t_avlt **node, char *key, char *value, int len)
{
	if (!*node)
	{
		if (create_avlt_node(node, key, value))
			return (insert_node(node, key, value, len));	
		return (false);
	}
	if (strncmp(key, (*node)->data[0], len) < 0)
		return (insert_node(&(*node)->left, key, value, len));
	else if (strncmp(key, (*node)->data[0], len) > 0)
		return (insert_node(&(*node)->right, key, value, len));
	(*node)->height = 1 + my_max(height((*node)->left), height((*node)->right));
	return (balance_tree(node, key, len));
}
*/

//New version
bool	create_avlt_node(t_avlt **new, t_env *node)
{
	if (!*new && node)
	{
		*new = (t_avlt *)malloc(sizeof(t_avlt));
		if (new)
		{
			(*new)->height = 1;
			(*new)->env = node;
			(*new)->left = NULL;
			(*new)->right = NULL;
		}
	}
	return (new);
}

//New version
bool	insert_avlt_node(t_avlt **node, t_env *env, int len)
{
	if (!*node)
	{
		if (create_avlt_node(node, env))
			return (insert_avlt_node(node, env, len));	
		return (false);
	}
	if (strncmp(env->var[KEY], (*node)->env->var[KEY], len) < 0)
		return (insert_avlt_node(&(*node)->left, env, len));
	else if (strncmp(env->var[KEY], (*node)->env->var[KEY], len) > 0)
		return (insert_avlt_node(&(*node)->right, env, len));
	(*node)->height = 1 + my_max(height((*node)->left), height((*node)->right));
	return (balance_tree(node, (*node)->env->var[KEY], len));
}

/*			NEEDS IMPLEMENTATION
 *
 *
bool	remove node(t_avlt *tree, char *key)
{
	if (tree)
	{

	}
}*/
