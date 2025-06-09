/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:25:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 18:47:06 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool words(t_tokn **current, char *delimiter)
{
    t_tokn  *new;
    t_tokn  *save;
    char    *word;
    char    *expanded;

    save = (*current)->next;
    expanded = (*current)->value;
    if (expanded)
    {
        word = strtok_r(expanded, delimiter, &expanded);
	    (*current)->value = word;
        word = strtok_r(expanded, delimiter, &expanded);
        while (word && expanded)
        {
            new = create_token_node(strdup(word), (*current)->type);
		    if (!new)
                break ;
		    (*current)->next = new;
		    *current = new;
            word = strtok_r(expanded, delimiter, &expanded);
        }
        (*current)->next = save;
    }
    return (!*expanded);
}

//We use this module to split tokens after their expansion.
bool	word_splitting(t_shell *minishell, t_tokn **current)
{
	t_env	*difsi;
	char	*delimiter;

	difsi = find_special_env_variable(minishell, DIFSI);
	if (!difsi)
		return (false);
	delimiter = difsi->var[VALUE];
	if (*current && delimiter)
        return (words(current, delimiter));
    return (false);
}
