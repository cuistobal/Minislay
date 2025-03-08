#ifndef AVL_TREE_H
# define AVL_TREE_H

/*Required standard headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

//AVL tree structure
typedef struct	avltree
{
	int				height;
	char			*data[2];
	struct avltree	*left;
	struct avltree	*right;
}	t_avlt;

//avl_utils.c:
int		height(t_avlt *node);
int		my_max(const int a, const int b);
void	pre_order_display(t_avlt *root);
bool	create_avlt_node(t_avlt **new, char *key, char *value);
bool	insert_node(t_avlt **node, char *key, char *value, int len);
void	free_avlt_tree(t_avlt *root);
bool	find_element(t_avlt *tree, t_avlt **node, char *key, char *value);

//rotations.c:
bool	balance_tree(t_avlt **node, char *key, char *value, int len);

#endif
