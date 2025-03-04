#include "avl_tree.h"

int	main(int argc, char **argv, char **envp)
{
	t_avlt	*root;

	(void)argc;
	(void)argv;
	root = NULL;
	if (create_avlt_node(&root, *envp))
	{
		envp++;
		while (*envp)
		{
			if (!insert_node(&root, *envp))
				break ;
			envp++;
		}
		pre_order_display(root);
	}
	return 0;
}

/*
int	main(int argc, char **argv, char **envp)
{
	char	*name;
	t_avlt	*root;

	(void)argc;
	(void)argv;
	root = NULL;
	name = strtok(*envp, "=");
	if (create_avlt_node(&root, name))
	{
		envp++;
		name = strtok(*envp, "=");
		while (*envp)
		{
			if (!insert_node(&root, name))
				break ;
			envp++;
			name = strtok(*envp, "=");
		}
		pre_order_display(root);
	}
	return 0;
}*/

/*
int	main(int argc, char **argv)
{
	t_avlt	*root;

	root = NULL;
	if (argc > 1)
	{
		argv++;
		if (create_avlt_node(&root, *argv))
		{
			argv++;
			while (*argv)
			{
				if (!insert_node(&root, *argv))
					break ;	
				argv++;
			}
			pre_order_display(root);
		}
	}
	return 0;
}*/
