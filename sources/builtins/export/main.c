#include "avl_tree.h"

//
static bool	create_tree(t_avlt **root, char **envp)
{
	int		len;
	char	*key;
	char	*value;

	while (*envp)
	{
		key = strdup(*envp);
		if (key)
		{
			strtok_r(key, "=", &value);
			len = strlen(key);
			if (!insert_node(root, key, value, len))
			{
				free(key);
				return (false);
			}
			free(key);		//Not what I wanted to do but there is a small leak
							//I can't fix otherwise :(
			envp++;
		}
	}
	return (!*envp);
}

//
int	main(int argc, char **argv, char **envp)
{
	t_avlt	*root;

	root = NULL;
	if (create_tree(&root, envp))
	{
		if (argc > 1)
		{	
			if (create_tree(&root, argv + 1))
				pre_order_display(root);
		}
	}
	free_tree(root);
	return 0;
}
