/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:25:02 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 13:25:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
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

    if (!branch)
		return (false);
    current = branch->tokens;
    while (current)
    {
    	current = current->next;
		if (current && current->type != CPAR)
		{
    		if (!append_prompt(prompt, current))
    	    	return (false);
		}
    }
	return (true);
}

//
bool	handle_subshell(t_shel *minishell, t_tree *ast)
{
	char	*subshell_command;

	subshell_command = NULL;
	if (prompt(&subshell_command, ast))
	{
		printf("SUBSHELL COMMAND	->	%s\n", subshell_command);
		if (get_minishelled(&minishell, subshell_command))
		{
			free(subshell_command);
			return (true);
		}
	}
	return (false);
}
