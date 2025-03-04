#include "minislay.h"

//
bool	insert_env_node(t_env **head, t_env **tail, t_env *new)
{
	if (new)
	{
		if (!*head)
		{
			*head = new;
			*tail = new;
		}
		else
		{
			(*tail)->next = new;
			*tail = new;
		}
	}
	return (new);
}

//
t_env	*create_env_node(char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new)
	{
		new->var = value;
		new->next = NULL;
	}
	return (new);
}
