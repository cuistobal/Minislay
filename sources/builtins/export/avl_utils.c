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

void	free_tree(t_avlt *root)
{
	if (root)
	{
		free_tree(root->left);
		free_tree(root->right);
		free(root->data[0]);
		free(root->data[1]);
		free(root);
	}
}

//This function prints the tree's content in pre_order (leftmost -> rightmost)
void	pre_order_display(t_avlt *root)
{
	if (root)
	{
		pre_order_display(root->left);
		printf("export %s", root->data[0]);
		printf("=%s\n", root->data[1]);
		pre_order_display(root->right);
	}
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

