/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:04:05 by ynyamets          #+#    #+#             */
/*   Updated: 2025/06/12 17:04:07 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	int	i;
	int	j;

	if (!s || !accept)
		return (NULL);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				return ((char *)(s + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
