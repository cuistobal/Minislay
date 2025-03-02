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

//This function prints the tree's content in pre_order (leftmost -> rightmost)
void	pre_order_display(t_avlt *root)
{
	if (root)
	{
		pre_order_display(root->left);
		printf("export %s\n", root->data);
		pre_order_display(root->right);
	}
}

//This function takes the adress of a t_avlt pointer and allocates & intialize
//its memory if it's NULL.
bool	create_avlt_node(t_avlt **new, char *data)
{
	if (!*new)
	{
		*new = (t_avlt *)malloc(sizeof(t_avlt));
		if (*new)
		{
			(*new)->height = 1;
			(*new)->data = data;
			(*new)->left = NULL;
			(*new)->right = NULL;
		}
	}
	return (*new);
}

//
bool	insert_node(t_avlt **node, char *data)
{
	if (!*node)
	{
		if (create_avlt_node(node, data))
			return (insert_node(node, data));
		return (false);
	}
	if (strcmp(data, (*node)->data) < 0)
		return (insert_node(&(*node)->left, data));
	else if (strcmp(data, (*node)->data) > 0)
		return (insert_node(&(*node)->right, data));
	(*node)->height = 1 + my_max(height((*node)->left), height((*node)->right));
	return (balance_tree(node, data));
}
