/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:42:37 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:44:09 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Needs a proper implementation
void	unset(void *p1, void *p2)
{
	char	*param;
	t_shel	*minishell;

	param = (char *)p2;
	minishell = (t_shel *)p1;
	if (!minishell || !param)
		return ;
	printf("%s\n", param);
}
