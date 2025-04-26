/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:23:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:27:01 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs a proper implementation ->	Once the key is splited from the value, we
//need to look trought the avl_tree and modify / insert the key accordingly.
void	export(void *p1, void *p2)
{
	char	*key;
	char	*value;
	char	*params;
	t_shel	*minishell;

	params = (char *)p2;
	minishell = (t_shel *)p1;
	key = strtok_r(params, "=", &params);
	if (!key)
		return ;
	value = params;
	printf("%s	=	%s\n", key, params);
}
