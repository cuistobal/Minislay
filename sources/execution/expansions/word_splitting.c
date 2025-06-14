/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:25:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:16:37 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/* static bool words(t_tokn **current, char *delimiter)
{
    t_tokn  *new;
    t_tokn  *save;
    char    *word;
    char    *expanded;

    save = (*current)->next;
    expanded = (*current)->value;
    if (expanded)
    {
        word = ft_strtok_r(expanded, delimiter, &expanded);
	    (*current)->value = word;
        word = ft_strtok_r(expanded, delimiter, &expanded);
        while (word && expanded)
        {
            new = create_token_node(ft_strdup(word), (*current)->type);
		    if (!new)
                break ;
		    (*current)->next = new;
		    *current = new;
            word = ft_strtok_r(expanded, delimiter, &expanded);
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
} */

static bool	words(t_tokn **current, char *delimiter)
{
	t_tokn	*new;
	t_tokn	*save;
	char	*word;
	char	*expanded;

	save = (*current)->next;
	expanded = (*current)->value;
	if (!expanded || !*expanded)
		return (true);
	word = ft_strtok_r(expanded, delimiter, &expanded);
	if (!word)
		return (true);
	(*current)->value = word;
	while (expanded && *expanded)
	{
		word = ft_strtok_r(expanded, delimiter, &expanded);
		if (!word)
			break ;
		new = create_token_node(ft_strdup(word), (*current)->type);
		if (!new)
			return (false);
		(*current)->next = new;
		*current = new;
	}
	return ((*current)->next = save, true);
}

//
bool	word_splitting(t_shell *minishell, t_tokn **current)
{
	t_env	*difsi;
	char	*delimiter;

	if (!current || !*current || !(*current)->value || !(*current)->value[0])
		return (true);
	difsi = find_special_env_variable(minishell, DIFSI);
	if (!difsi || !difsi->var[VALUE])
		return (true);
	delimiter = difsi->var[VALUE];
	return (words(current, delimiter));
}
