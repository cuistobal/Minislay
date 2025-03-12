#include "minislay.h"

/*
//
static bool build_export(t_shel **minishell)
{
	t_avlt	*new;
	t_env	*current;

	current = NULL;
	if (*minishell)
	{
		//Needs building after merging the builtin branch			
		current = (*minishell)->envp;
		while (current)
		{
			new = create_avlt_node(current);
			if (!new)
				break ;
			insert()
			current = current->next;	
		}
	}
	return false;
}*/

//
static bool build_env(t_shel **minishell, char **envp)
{
    t_env	*new;
    t_env	*tail;
    t_env	**head;

    if (*minishell)
    {
		new = NULL;
        tail = NULL;
		head = &(*minishell)->envp;
		while (*envp)
        {
        	new = create_env_node(strdup(*envp));
			if (!new)	
				return (false);
            insert_env_node(head, &tail, new);
			insert_avlt_node(&(*minishell)->expt, new, strlen(new->var[KEY]));
			envp++;
		}
    }
    return (!*envp);
}

//
bool    set_env(t_shel **minishell, char **envp)
{
    if (*minishell)
        return (build_env(minishell, envp));
    return (false);
}
