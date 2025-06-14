/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:44:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:18:42 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*joined;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 || !*s1)
	{
		if (s2)
			return (ft_strdup(s2));
		return (ft_strdup(""));
	}
	if (!s2 || !*s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (size + 1));
	if (!joined)
		return (NULL);
	join_s1(s1, joined);
	join_s2(s2, joined + ft_strlen(s1));
	joined[size] = '\0';
	return (joined);
}
