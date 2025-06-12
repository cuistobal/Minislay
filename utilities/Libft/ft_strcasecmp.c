/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:29:54 by ynyamets          #+#    #+#             */
/*   Updated: 2025/06/12 17:29:58 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		c1 = (unsigned char)to_lower(c1);
		c2 = (unsigned char)to_lower(c2);
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}
