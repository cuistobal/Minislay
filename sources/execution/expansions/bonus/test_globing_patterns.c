/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_globing_patterns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:11:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/29 11:12:15 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*create_sub_string(const char *string, int length)
{
	if (string)
		return (strndup(string, length));
	return (NULL);
}

//
static char	*handle_words(const char *globing, int *index)
{
	int	start;

	if (!globing)
		return (NULL);
	start = *index;
	while (globing[*index])
	{
		(*index)++;
		if (!globing[*index] || globing[*index] == '*')
			break ;
	}
	return (create_sub_string(globing + start, *index - start));
}

//
static char	*handle_stars(const char *globing, int *index)
{
	int	start;

	if (!globing)
		return (NULL);
	start = *index;
	while (globing[*index])
	{
		(*index)++;
		if (!globing[*index] || globing[*index] != '*')
			break ;
	}
	return (create_sub_string(globing + start, 1));
}

//
static char *handle_pattern(char *globing, int *index)
{
	char	*new;

	new = NULL;
	if (globing[*index] == '*')
		new = handle_stars(globing, index);
	else
		new = handle_words(globing, index);
	return (new);
}

//We use this function to identify the patterns within the the globing variable
char	**identify_globing_patterns(char *globing)
{
	int		index;
	int		pindex;
	char	**patterns;
	
	patterns = NULL;
	if (!globing)
		return (NULL);
	index = 0;	
	pindex = 0;
	while (globing[index])
	{	
		pindex++;
		patterns = (char **)realloc(patterns, sizeof(char *) * (pindex + 1));
		if (!patterns)
			return (NULL);
		patterns[pindex - 1] = handle_pattern(globing, &index);
		patterns[pindex] = NULL;
		if (!patterns[pindex - 1])
			break ;
	}
	if (globing[index] != '\0')
		return (free_array(patterns, pindex), NULL);
	return (patterns);
}
