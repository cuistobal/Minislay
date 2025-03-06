#include "minislay.h"

static bool append_prompt(char **prompt, t_tokn *current)
{
    char    *joined;

    joined = NULL;
    if (current)
    {
        joined = ft_strjoin(*prompt, current->value);
        if (joined)
        {
            free(*prompt);
            *prompt = joined;
        	joined = ft_strjoin(*prompt, " ");
			if (joined)
			{
            	free(*prompt);
            	*prompt = joined;
				return (true);
			}
        }
    }
    return (false);
}

//We use this function to turn the subshell part of the list into a string.
//Hence, we can eprform recursive call to minishell.
static bool	prompt(char **prompt, t_tree *branch)
{

    t_tokn  *current;

    if (branch)
    {
        current = branch->tokens;
        while (current)
        {
			if (current->type != OPAR && current->type != CPAR)
			{
            	if (!append_prompt(prompt, current))
                	return (false);
			}
            current = current->next;
        }
    }
	return (branch);
}

bool	handle_subshell(t_shel *minishell, t_tree *ast)
{
	t_shel	*copy;
	char	*subshell_command;

	copy = minishell;
	subshell_command = NULL;
	if (prompt(&subshell_command, ast))
	{
		printf("SUBSHELL COMMAND	->	%s\n", subshell_command);
		if (get_minishelled(&copy, subshell_command))
		{
			free(subshell_command);
			return true;
		}
	}
	return false;
}
