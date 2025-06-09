/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:44:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 18:17:23 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include "minislay.h"

//Appends s2 to the joined string
static char	*join_s1(const char *s1, char *joined)
{
	size_t	string_index;

	string_index = 0;
	while (s1[string_index] != '\0')
	{
		*joined = s1[string_index];
		string_index++;
		joined++;
	}
	return (joined);
}

//Appends s1 to the joined string
static char	*join_s2(const char *s2, char *joined)
{
	size_t	string_index;

	string_index = 0;
	while (s2[string_index] != '\0')
	{
		*joined = s2[string_index];
		string_index++;
		joined++;
	}
	return (joined);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    size_t  size;
    char    *joined;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (strdup(s2));
    if (!s2)
        return (strdup(s1));
    if (!*s1 && !*s2)
        return (NULL);
    size = strlen(s1) + strlen(s2);
    joined = (char *)malloc(sizeof(char) * (size + 1));
    if (!joined)
        return (NULL);
    join_s1(s1, joined);
    join_s2(s2, joined + strlen(s1));
    joined[size] = '\0';
    return (joined);
}
