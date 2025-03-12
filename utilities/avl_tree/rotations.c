#include "minislay.h"

//
static bool	get_balance(t_avlt *node, int *balance)
{
	if (node)
	{
		*balance = height(node->left) - height(node->right);
		return (true);
	}
	return (false);
}

//
static void	right_rotate(t_avlt **y)
{
	t_avlt	**x;
	t_avlt	**t2;

	x = &(*y)->left;
	t2 = &(*x)->right;
	(*x)->right = *y;
	(*y)->left = *t2;
	(*y)->height = my_max(height((*y)->left), height((*y)->right)) + 1;
	(*x)->height = my_max(height((*x)->left), height((*x)->right)) + 1;
}

//
static void	left_rotate(t_avlt **x)
{
	t_avlt	**y;
	t_avlt	**t2;

	y = &(*x)->right;
	t2 = &(*y)->left;
	(*y)->left = *x;
	(*x)->right = *t2;
	(*x)->height = my_max(height((*x)->left), height((*x)->right)) + 1;
	(*y)->height = my_max(height((*y)->left), height((*y)->right)) + 1;
}

//
bool	balance_tree(t_avlt **node, char *key, int len)
{
	int		balance;
	
	balance = 0;
	if (get_balance(*node, &balance))
	{
		if (balance > 1 && strncmp(key, (*node)->left->env->var[KEY], len) < 0)
			right_rotate(node);
		if (balance < -1 && strncmp(key, (*node)->right->env->var[KEY], len) > 0)
			left_rotate(node);
		if (balance > 1 && strncmp(key, (*node)->left->env->var[KEY], len) > 0)
		{
			left_rotate(&(*node)->left);
			right_rotate(node);
		}
		if (balance < -1 && strncmp(key, (*node)->right->env->var[KEY], len) < 0)
		{
			right_rotate(&(*node)->right);
			left_rotate(node);
		}
		return (true);
	}
	return (false);
}
