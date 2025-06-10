/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 16:55:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
static inline bool	is_hidden_file(char *current, int i)
{
	return (i == 0 && *current == '.');
}

//
bool	match_pattern(char **patterns, char *current, int *i)
{
	char	*temp;

	if (!patterns || !current)
		return (false);
	temp = NULL;
	if (!patterns[*i])
		return (true);
	if	(strcmp(patterns[*i], "*") == 0)
	{
		if (is_hidden_file(current, *i))
			return (false);
		return ((*i)++, match_pattern(patterns, current, i));
	}
	else
	{
		temp = strstr(current, patterns[*i]);
		if (temp && *temp == *current)
			return ((*i)++, match_pattern(patterns, temp + strlen(temp), i));
		return (false);
	}
	return (true);
}



** Checks if file is hidden (starts with '.')
** Only considered hidden if it's the first character and not explicitly matched

static inline bool	is_hidden_file(const char *current, int pattern_index)
{
    return (pattern_index == 0 && *current == '.');
}


** Matches a single pattern against a string
** - '*' matches any sequence of characters
** - Non-'*' characters must match exactly
** - Handles pattern position constraints

static bool	match_single_pattern(const char *pattern, const char *str)
{
    size_t	pat_len;
    size_t	str_len;
    char	*star_pos;

    if (!pattern || !str)
        return (false);
    pat_len = strlen(pattern);
    str_len = strlen(str);
    star_pos = strchr(pattern, '*');

    // No wildcard, exact match required
    if (!star_pos)
        return (strcmp(pattern, str) == 0);

    // Pattern starts with '*': match anywhere in string
    if (star_pos == pattern)
        return (strstr(str, pattern + 1) != NULL);

    // Pattern ends with '*': match prefix
    if (star_pos == pattern + pat_len - 1)
        return (strncmp(pattern, str, pat_len - 1) == 0);

    // Pattern has '*' in middle: match before and after
    *star_pos = '\0';
    if (strncmp(pattern, str, star_pos - pattern) != 0)
        return (*star_pos = '*', false);
    *star_pos = '*';
    return (strstr(str + (star_pos - pattern), star_pos + 1) != NULL);
}


** Main pattern matching function
** - Handles multiple patterns
** - Checks for hidden files
** - Returns true if all patterns match

bool	match_pattern(char **patterns, char *current, int *i)
{
    if (!patterns || !current)
        return (false);
    if (!patterns[*i])
        return (true);
    if (is_hidden_file(current, *i))
        return (false);
    return (match_single_pattern(patterns[*i], current) && \
            ((*i)++, match_pattern(patterns, current, i)));
}
*/

//
bool	match_pattern(char *pattern, char *current)
{
	if (*pattern == '\0' && *current == '\0')
		return (true);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, current) ||\
				(*current && match_pattern(pattern, current + 1)));
	if (*pattern == '?' || *pattern == *current)
		return (match_pattern(pattern + 1, current + 1));
	return (false);
}

