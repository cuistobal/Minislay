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
	char	*key;
	char	*value;
	t_avlt	*root;
	t_avlt	*find;

	find = NULL;
	root = NULL;
	if (create_tree(&root, envp))
	{
		if (argc > 1)
		{
			argv++;
			while (*argv)
			{
				key = strdup(*argv);
				strtok_r(key, "=", &value);
				if (find_element(root, &find, key, value))
				{
					printf("key was found	->	%s\n", find->data[1]);
					free(find->data[1]);
					find->data[1] = strdup(value);
					printf("new value is	->	%s\n", find->data[1]);
				}
				else
					printf("%s is not part of the environement\n", key);
				free(key);
				argv++;
			}
		}
		//pre_order_display(root);
	}
	free_avlt_tree(root);
	return 0;
}
