/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:40:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:16:37 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this utility to extract the key within the current token string.
static char	*extract_key(char *token, int *index, int start)
{
	int	tlen;

	tlen = 0;
	while (token[*index])
	{
		(*index)++;
		if (!isalnum(token[*index]) && token[*index] != '_')
		{
			if (tlen == 0)
			{
				if (ft_strchr(SPE_EXP_CHAR, token[*index]))
				{
					tlen++;
					(*index)++;
				}
				return (ft_strndup(token + start, tlen + 1));
			}
			break ;
		}
		tlen++;
	}
	return (ft_strndup(token + start, tlen + 1));
}

//
static void	quote_state(char current, char *quote, bool *sqte)
{
	if (is_quote(current))
	{
		if (!*quote)
		{
			*quote = current;
			*sqte = *quote == '\'';
		}
		else if (*quote == current)
		{
			*quote = INIT;
			*sqte = *quote == '\'';
		}
	}
}

//We use this utility to discriminate keys and non keys within the current token
//string.
//This is where we should implement the SQTE DQTE discrimination. POssibly using
//a stack approach where we pile the quotes if peek() == token[index].
static char	*retrieve_expansions(char *token, int *index)
{
	bool		sqte;
	int			start;
	static char	quote;

	sqte = false;
	start = *index;
	if (*index == 0)
		quote = INIT;
	if (token[*index])
	{
		while (token[*index])
		{
			quote_state(token[*index], &quote, &sqte);
			if (token[*index] == '$' && !sqte)
			{
				if (*index == start)
					return (extract_key(token, index, start));
				return (ft_strndup(token + start, *index - start));
			}
			(*index)++;
		}
		return (ft_strdup(token + start));
	}
	return (NULL);
}

//We use this function to determine if the key is a standard key or an env/user
//defined key.
static bool	retrieve_keys_value(t_shell *minishell, char *key, char **value)
{
	if (key)
	{
		if (*key != '$')
			*value = ft_strdup(key);
		else
		{
			if (!is_standard_key(minishell, value, key))
			{
				if (!find_key(minishell, value, key + 1))
					return (false);
			}
			*value = ft_strdup(*value);
		}
		return (*value);
	}
	return (*key);
}

/* //
bool	get_expanded(t_shell *minishell, char *token, char **value, int *index)
{
	char	*key;

	key = NULL;
	if (token && token[*index])
	{
		key = retrieve_expansions(token, index);
		if (key)
		{
			if (!retrieve_keys_value(minishell, key, value)) 
				*value = ft_strdup("");
			free(key);
			key = NULL;
			return (true);
		}
	}
	return (!token[*index]);
}
 */
bool	get_expanded(t_shell *minishell, char *token, char **value, int *index)
{
	bool	ret;
	char	*key;

	key = NULL;
	ret = false;
	if (token && token[*index])
	{
		key = retrieve_expansions(token, index);
		if (key)
		{
			if (!retrieve_keys_value(minishell, key, value))
			{
				*value = ft_strdup("");
				ret = true;
			}
			else
				ret = true;
			free(key);
			key = NULL;
		}
	}
	if (ret)
		return (true);
	return (!token[*index]);
}
