/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:10:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Modify the PWD && OLDPWD variables
// If OLDPWD == CDPATH -> printf(PWD)
//void	cd(t_shel *minishell, char *path)
void	cd(void *p1, void *p2)
{
	char	*path;
	t_shel	*minishell;


	path = (char *)p2;
	minishell = (t_shel *)p1;
	if (!minishell || !path)
		return ;
	if (is_absolute(path))
		printf("%s\n", path);
	else
		printf("%s\n", path);
}
