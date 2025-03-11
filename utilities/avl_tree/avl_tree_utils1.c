#include "minislay.h"

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
		printf("export %s", root->data[0]);
		printf("=%s\n", root->data[1]);
		pre_order_display(root->right);
	}
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
