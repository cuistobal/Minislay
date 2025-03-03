#include "minislay.h"

static bool build_export(t_shel **minishell)
{

}

static bool build_env(t_envp **mini_env, char **envp)
{
    t_env   *new;
    char    *value;
    char    *variable;

    if ()
    {
        while (*envp)
        {
            variable = my_strtok_r(*envp, "=", &value);
            if (variable)
            {
                new = create_env_node(variable, value);
                if (!new)
                    break ;
                insert_env_node();
            }
            envp++;
        }
        return (!*envp);
    }
    return (false);
}

bool    set_env(t_shel **minishell, char **envp)
{
    if (*minishell)
    {
        (*minishell)->envp = (t_envp *)malloc(sizeof(t_envp));
        if ((*minishell)->envp)
        {
            if (build_env(&(*minishell)->envp, envp))
                return (build_export(minishell));
        }
    }
    return (false);
}
