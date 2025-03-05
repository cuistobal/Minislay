#include "minislay.h"

static bool append_prompt(char **prompt, t_tokn *current)
{
    char    *joined;

    joined = NULL;
    if (current)
    {
        joined = strjoini(*prompt, current->value);
        if (joined)
        {
            free(prompt);
            prompt = joined;
            return (true);
        }
    }
    return (false);
}

//We use this function to turn the subshell part of the list into a string.
//Hence, we can eprform recursive call to minishell.
bool    prompt(char **prompt, t_tree *branch)
{
    t_tokn  *current;

    if (branch)
    {
        current = branch->tokens;
        while (current)
        {
            if (!append_prompt(prompt, current))
                return (false);
            current = current->next;
        }
    }
}
