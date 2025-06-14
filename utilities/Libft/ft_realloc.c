/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:43:01 by ynyamets          #+#    #+#             */
/*   Updated: 2025/06/12 20:57:13 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	**ft_realloc(void **ptr, int old_size, int new_size)
{
	void	**new_ptr;
	int		i;

	new_ptr = malloc(sizeof(void *) * new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	while (i < new_size)
	{
		new_ptr[i] = NULL;
		i++;
	}
	free(ptr);
	return (new_ptr);
}
