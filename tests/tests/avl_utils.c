/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:59:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 14:59:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl_tree.h"

//
int	height(t_avlt *node)
{
	if (node)
		return (node->height);
	return (0);
}

//
int	my_max(const int a, const int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	free_avlt_tree(t_avlt *root)
{
	if (!root)
		return ;
	free_avlt_tree(root->left);
	root->left = NULL;
	free_avlt_tree(root->right);
	root->right = NULL;
	if (root->data[0])
	{
		free(root->data[0]);
		root->data[0] = NULL;
	}
	if (root->data[1])
	{
		free(root->data[1]);
		root->data[1] = NULL;
	}
	free(root);
	root = NULL;
}

//This function prints the tree's content in pre_order (leftmost -> rightmost)
void	pre_order_display(t_avlt *root)
{
	if (!root)
		return ;
	pre_order_display(root->left);
	printf("export %s", root->data[0]);
	printf("=%s\n", root->data[1]);
	pre_order_display(root->right);
}

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
	return (balance_tree(node, key, value, len));
}

//
bool	find_element(t_avlt *tree, t_avlt **node, char *key, char *value)
{
	if (tree)
	{
		if (tree->data[0])
		{
			if (strcmp(key, tree->data[0]) == 0)
			{
				*node = tree;
				return (true);
			}
			else
			{
				if (strcmp(key, tree->data[0]) < 0)
					return (find_element(tree->left, node, key, value));
				return (find_element(tree->right, node, key, value));
			}
		}
	}
	return (false);
}
