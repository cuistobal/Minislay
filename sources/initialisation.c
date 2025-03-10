#include "minislay.h"

/*
static bool build_export(t_shel **minishell)
{
	t_avlt	*new;
	t_env	*current;

	current = NULL;
	if (*minishell)
	{
		if ((*minishell)->envp)
		{
			//Needs building after merging the builtin branch			
			current = (*minishell)->envp->envp;
			while (current)
			{
				new = create_avlt_node(current->var);
				if (!new)
					break ;
				insert()
				current = current->next;	
			}
		}
	}
	return false;
}*/

static bool build_env(t_shel **minishell, char **envp)
{
    t_env	*new;
    t_env	*tail;
    t_env	**head;
    char	*variable;

    if (*minishell)
    {
		new = NULL;
        tail = NULL;
		head = &(*minishell)->envp;
		while (*envp)
        {
            variable = strdup(*envp);
            if (variable)
            {
                new = create_env_node(variable);
                if (!new)
				{
					free (variable);
                    break ;
				}
                insert_env_node(head, &tail, new);
			}
            envp++;
        }
        return (!*envp);
    }
    return (false);
}

//
bool    set_env(t_shel **minishell, char **envp)
{
    if (*minishell)
        return (build_env(minishell, envp));
    return (false);
}
