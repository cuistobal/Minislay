#include "minislay.h"

Expansion found ? realloc

static bool handle_regular_expansions()
{

}

static bool handle_dqte_expansions()
{
    
}

//Entry point of the expansion module
bool    expand(t_shel *minishell, t_tokn *token)
{
    int     index;
    char    expanded;

    if (minishell && token)
    {
        if (token->type & DQTE)

        else

    }
}
