#include "minislay.h"

//Prints the environement variables
bool	env(t_shel *minishell)
{
    if (minishell)
    {
        if (minishell->envp)
        {
            while(minishell->envp->envp)
            {
                printf("%s\n", minishell->envp->envp->var);
                minishell->envp->envp = minishell->envp->envp->next;
            }
            return (true);
        }
    }
    return (false);
}
